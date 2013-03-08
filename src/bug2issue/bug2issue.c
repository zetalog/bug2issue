#ifdef WIN32
#include <winsock.h>
#include <direct.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <getopt.h>
#include <json.h>
#include <mysql.h>
#include <errmsg.h>
#include <curl/curl.h>

#define SQL_DOWN			1 /* for re-connect */
#define CURL_NAME           "curl"
#define CURL_USERAGENT      CURL_NAME "/" LIBCURL_VERSION
#define ALLOC_MINIMUM       512

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define foreach_array(idx, array, string)            \
    for ((idx) = 0, (string) = (array)[0]; (idx) < ARRAY_SIZE((array)); (idx)++, (string) = (array)[idx]) \

typedef char **sql_row_t;
typedef unsigned long *sql_len_t;
typedef const char *github_color_t;

struct mysql_conn {
    MYSQL conn;
    MYSQL *sock;
    MYSQL_RES *result;
    sql_row_t row;
};

struct bug2issue_cfg {
    unsigned long mode;
#define BUG2ISSUE_EXPORT_ISSUE      0x0001
#define BUG2ISSUE_EXPORT_COMMENT    0x0002
#define BUG2ISSUE_EXPORT_ATTACHMENT 0x0004
#define BUG2ISSUE_UPLOAD_GITHUB     0x0010
#define BUG2ISSUE_LABEL_FIELD       0x0020
#define BUG2ISSUE_LABEL_COMPONENT   0x0040
#define BUG2ISSUE_TITLE_BUGIDS      0x0080
#define BUG2ISSUE_LIST_BUGID        0x8000

    char *sql_server;
    char *sql_port;
    char *sql_login;
    char *sql_password;
    char *sql_db;
    struct mysql_conn *conn;
    sql_row_t row;
    sql_len_t lens;

    const char *bugzilla_product;

    /* CURL related */
    char *github_repo;
    char *github_user;
    char *github_issue_url;
    char *github_label_url;

    CURL *curl;
    char *curl_output_buf;
    size_t curl_alloc_size;
    size_t curl_store_size;

    struct array_list *close_states;
    struct array_list *field_labels;
    struct array_list *exist_labels;

    char *issues_dir;
    char *bug_id;
    json_object *bugs;
    json_object *comments;
};

struct bug2issue_cfg bug2issue;

static const char *bugzilla_issues_query = "select "
    "bugs.bug_id "
    "from bugs "
    "order by bugs.bug_id;";

static const char *bugzilla_issue_query = "select "
    "bugs.bug_id,"
    "bugs.short_desc,"
    "bugs.bug_file_loc,"
    "products.name product,"
    "components.name component,"
    "reporter.login_name reporter_email,"
    "reporter.realname reporter_name,"
    "assigned_to.login_name assigned_to_email,"
    "assigned_to.realname assigned_to_name,"
    "bugs.creation_ts,"
    "bugs.delta_ts,"
    "bugs.lastdiffed,"
    "bugs.resolution,"
    "bugs.rep_platform,"
    "bugs.op_sys,"
    "bugs.version,"
    "bugs.priority,"
    "bugs.bug_severity,"
    "bugs.bug_status "
    "from bugs "
    "left join products on "
        "products.id=bugs.product_id "
    "left join components on "
        "components.id=bugs.component_id "
    "left join profiles reporter on "
        "reporter.userid=bugs.reporter "
    "left join profiles assigned_to on "
        "assigned_to.userid=bugs.assigned_to "
    "where bugs.bug_id=%s "
    "order by bugs.bug_id;";
#define BUG_ID_INDEX            0
#define BUG_TITLE_INDEX         1
#define BUG_PRODUCT_INDEX       3
#define BUG_COMPONENT_INDEX     4
#define BUG_EMAIL_INDEX         5
#define BUG_CNAME_INDEX         6
#define BUG_CREATE_INDEX        9
#define BUG_RESOLUTION_INDEX    12
#define BUG_PLATFORM_INDEX      13
#define BUG_OS_INDEX            14
#define BUG_VERSION_INDEX       15
#define BUG_PRIORITY_INDEX      16
#define BUG_SEVERITY_INDEX      17
#define BUG_STATUS_INDEX        18
static const char *bugzilla_issue_columns[] = {
    "bug_id",
    "short_desc",
    "bug_file_loc",
    "product",
    "component",
    "reporter_email",
    "reporter_name",
    "assigned_to_email",
    "assigned_to_name",
    "creation_ts",
    "delta_ts",
    "lastdiffed",
    "resolution",
    "rep_platform",
    "op_sys",
    "version",
    "priority",
    "bug_severity",
    "bug_status",
};

static const char *bugzilla_comments_query = "select "
    "longdescs.comment_id,"
    "longdescs.bug_when "
    "from longdescs "
    "where longdescs.bug_id=%s "
    "order by longdescs.comment_id, longdescs.bug_when;";

#define CMT_EMAIL_INDEX     2
#define CMT_CNAME_INDEX     3
#define CMT_CREATE_INDEX    4
#define CMT_TEXT_INDEX      5
#define CMT_ATT_ID_INDEX    6
#define CMT_ATT_NAME_INDEX  7
#define CMT_ATT_MIME_INDEX  8
#define CMT_ATT_DESC_INDEX  9
static const char *bugzilla_comment_query = "select "
    "longdescs.bug_id,"
    "longdescs.comment_id,"
    "who.login_name who_email,"
    "who.realname who_name,"
    "longdescs.bug_when,"
    "longdescs.thetext,"
    "attachments.attach_id,"
    "attachments.filename attach_filename,"
    "attachments.mimetype attach_mimetype,"
    "attachments.description attach_description,"
    "attach_data.thedata attach_thedata "
    "from longdescs "
    "left join profiles who on "
        "who.userid=longdescs.who "
    "left join attachments on "
        "attachments.creation_ts=longdescs.bug_when "
    "and "
        "attachments.bug_id=longdescs.bug_id "
    "and "
        "attachments.submitter_id=longdescs.who "
    "left join profiles submitter on "
        "submitter.userid=attachments.submitter_id "
    "left join attach_data on "
        "attach_data.id=attachments.attach_id "
    "where longdescs.comment_id=%s;";
static const char *bugzilla_comment_columns[] = {
    "bug_id",
    "comment_id",
    "who_email",
    "who_name",
    "bug_when",
    "thetext",
    "attach_id",
    "attach_filename",
    "attach_mimetype",
    "attach_description",
    "attach_thedata",
};

static const char *bugzilla_attach_query = "select "
    "longdescs.bug_id,"
    "longdescs.comment_id,"
    "longdescs.bug_when,"
    "attachments.attach_id,"
    "attachments.filename attach_filename,"
    "attachments.mimetype attach_mimetype,"
    "attachments.description attach_description,"
    "attach_data.thedata attach_thedata "
    "from longdescs "
    "left join attachments on "
        "attachments.creation_ts=longdescs.bug_when "
    "and "
        "attachments.bug_id=longdescs.bug_id "
    "left join attach_data on "
        "attach_data.id=attachments.attach_id "
    "where longdescs.comment_id=%s;";
#define ATT_BUG_ID_INDEX        0
#define ATT_CMT_ID_INDEX        1
#define ATT_ATT_ID_INDEX        3
#define ATT_FNAME_INDEX         4
#define ATT_MIME_INDEX          5
#define ATT_CONTENT_INDEX       7
static const char *bugzilla_attach_columns[] = {
    "bug_id",
    "comment_id",
    "bug_when",
    "attach_id",
    "attach_filename",
    "attach_mimetype",
    "attach_description",
    "attach_thedata",
};

static const char *bugzilla_field_query = "select "
    "value "
    "from %s "
    "where isactive = 1 "
    "order by sortkey, value;";
#define FLD_VALUE_INDEX     0

static const char *bugzilla_component_query = "select "
    "products.name product_name,"
    "products.id product_id,"
    "components.name component_name "
    "from products "
    "left join components on "
        "components.product_id=products.id "
    "where products.name=\"%s\";";
#define COMP_VALUE_INDEX    2
static const char *bugzilla_component_columns[] = {
    "product_name",
    "product_id",
    "component_name",
};

const char *github_label_fields[] = {
    "rep_platform",
    "op_sys",
    "priority",
    "bug_severity",
    "bug_status",
    "resolution",
};

github_color_t github_label_colors[] = {
    "FF0000",
    "FFA500",
    "FFFF00",
    "00FF00",
    "007FFF",
    "0000FF",
    "8B00FF",
};

static void bug2issue_json_free_dummy(void *data)
{
    /* nop */
}

static int bug2issue_mysql_error(int error, const char *errmsg)
{
    if (!error)
        return 0;

    switch (error) {
    case CR_SERVER_GONE_ERROR:
    case CR_SERVER_LOST:
    case -1:
        fprintf(stderr,
                "mysql: error: %d, returning SQL_DOWN\n", error);
        return SQL_DOWN;
    case CR_OUT_OF_MEMORY:
    case CR_COMMANDS_OUT_OF_SYNC:
    case CR_UNKNOWN_ERROR:
    default:
        fprintf(stderr,
                "mysql: error: %d\n%s\n", error, errmsg);
        return -1;
    }
}

static int bug2issue_mysql_init(void)
{
    int ret = 0;
    struct mysql_conn *mysql_sock;

    if (!bug2issue.conn) {
        mysql_sock = (struct mysql_conn *)malloc(sizeof(struct mysql_conn));
        if (!mysql_sock) {
            fprintf(stderr, "mysql: malloc(mysql_conn) failure.\n");
            return -1;
        }
        memset(mysql_sock, 0, sizeof(*mysql_sock));

        mysql_init(&(mysql_sock->conn));
        mysql_options(&(mysql_sock->conn), MYSQL_READ_DEFAULT_GROUP, bug2issue.sql_db);
        mysql_sock->sock = mysql_real_connect(&(mysql_sock->conn),
                                              bug2issue.sql_server,
                                              bug2issue.sql_login,
                                              bug2issue.sql_password,
                                              bug2issue.sql_db,
                                              atoi(bug2issue.sql_port),
                                              NULL,
                                              CLIENT_FOUND_ROWS);
        if (mysql_sock->sock)
            bug2issue.conn = mysql_sock;
        else {
            fprintf(stderr, "mysql: mysql_real_connect failure.\n");
            fprintf(stderr, "mysql: username@host:database - %s@%s:%s\n",
                    bug2issue.sql_login, bug2issue.sql_server, bug2issue.sql_db);
            ret = bug2issue_mysql_error(mysql_errno(&mysql_sock->conn),
                                        mysql_error(&mysql_sock->conn));
            mysql_sock->sock = NULL;
        }
    }

    return ret;
}

static void bug2issue_mysql_exit(void)
{
    if (bug2issue.conn) {
       struct mysql_conn *mysql_sock = bug2issue.conn;

        if (mysql_sock->sock) {
            mysql_close(mysql_sock->sock);
            mysql_sock->sock = NULL;
        }
        bug2issue.conn = NULL;
    }
}

static void bug2issue_mysql_free_result(void)
{
    struct mysql_conn *mysql_sock = bug2issue.conn;

    if (mysql_sock->result) {
        mysql_free_result(mysql_sock->result);
        mysql_sock->result = NULL;
    }
}

static int bug2issue_mysql_query(const char *querystr)
{
    struct mysql_conn *mysql_sock = bug2issue.conn;
    int ret;

    if (mysql_sock->sock == NULL) {
        fprintf(stderr, "mysql: not connected.\n");
        return SQL_DOWN;
    }
    mysql_query(mysql_sock->sock, querystr);
    ret = bug2issue_mysql_error(mysql_errno(mysql_sock->sock),
                                mysql_error(mysql_sock->sock));

    return ret;
}

static int bug2issue_mysql_store_result(void)
{
    struct mysql_conn *mysql_sock = bug2issue.conn;
    int ret = 0;

    if (mysql_sock->sock == NULL) {
        fprintf(stderr, "mysql: not connected.\n");
        return SQL_DOWN;
    }

    mysql_sock->result = mysql_store_result(mysql_sock->sock);
    if (!mysql_sock->result) {
        fprintf(stderr, "mysql: mysql_store_result failure.\n");
        ret = bug2issue_mysql_error(mysql_errno(mysql_sock->sock),
                                    mysql_error(mysql_sock->sock));
    }

    return ret;
}

static int bug2issue_mysql_num_fields(void)
{
    int num = 0;
    struct mysql_conn *mysql_sock = bug2issue.conn;

#if MYSQL_VERSION_ID >= 32224
    num = mysql_field_count(mysql_sock->sock);
#else
    num = mysql_num_fields(mysql_sock->sock);
#endif
    if (!num) {
        fprintf(stderr, "mysql: mysql_num_fields - No Fields\n");
        bug2issue_mysql_error(mysql_errno(&mysql_sock->conn),
                              mysql_error(&mysql_sock->conn));
    }

    return num;
}

static int bug2issue_mysql_select(const char *querystr)
{
    int ret;

    ret = bug2issue_mysql_query(querystr);
    if (ret) return ret;
    ret = bug2issue_mysql_store_result();
    if (ret) return ret;
    bug2issue_mysql_num_fields();

    return ret;
}

static int bug2issue_mysql_fetch(void)
{
    int ret = 0;
    struct mysql_conn *mysql_sock = bug2issue.conn;

    if (!mysql_sock->result)
        return SQL_DOWN;

    bug2issue.row = mysql_fetch_row(mysql_sock->result);
    bug2issue.lens = mysql_fetch_lengths(mysql_sock->result);
    if (bug2issue.row == NULL)
        ret = bug2issue_mysql_error(mysql_errno(mysql_sock->sock),
                                    mysql_error(mysql_sock->sock));

    return ret;
}

static int bug2issue_curl_required(void)
{
    return bug2issue.mode & BUG2ISSUE_UPLOAD_GITHUB;
}

static void bug2issue_add_close_status(const char *status)
{
    assert(bug2issue.close_states);
    array_list_add(bug2issue.close_states, (void *)status);
}

static int bug2issue_is_closed_bug(const char *status)
{
    int nr_status, idx;
    const char *close_status;
    
    assert(bug2issue.close_states);
    nr_status = array_list_length(bug2issue.close_states);
    for (idx = 0; idx < nr_status; idx++) {
        close_status = (const char *)array_list_get_idx(bug2issue.close_states, idx);
        if (close_status && strcmp(close_status, status) == 0)
            return 1;
    }

    return 0;
}

static int bug2issue_is_exist_label(const char *label)
{
    int nr_labels, idx;
    const char *exist_label;
    
    assert(bug2issue.exist_labels);
    nr_labels = array_list_length(bug2issue.exist_labels);
    for (idx = 0; idx < nr_labels; idx++) {
        exist_label = (const char *)array_list_get_idx(bug2issue.exist_labels, idx);
        if (exist_label && strcmp(exist_label, label) == 0)
            return 1;
    }

    return 0;
}

static int bug2issue_add_field_label(const char *field)
{
    int idx;
    const char *iter;
    int label_possible = 0;

    assert(bug2issue.field_labels);

    foreach_array(idx, github_label_fields, iter) {
        if (strcmp(iter, field) == 0) {
            label_possible = 1;
            break;
        }
    }

    if (!label_possible)
        return -EINVAL;

    array_list_add(bug2issue.field_labels, (void *)field);
    bug2issue.mode |= BUG2ISSUE_LABEL_FIELD;

    return 0;
}

static int bug2issue_is_labeled_field(const char *field)
{
    int nr_fields, idx;
    const char *field_name;
    
    assert(bug2issue.field_labels);
    nr_fields = array_list_length(bug2issue.field_labels);
    for (idx = 0; idx < nr_fields; idx++) {
        field_name = (const char *)array_list_get_idx(bug2issue.field_labels, idx);
        if (field_name && strcmp(field_name, field) == 0)
            return 1;
    }

    return 0;
}

static size_t bug2issue_curl_write_cb(void *buffer,
                                      size_t sz, size_t nmemb,
                                      void *userdata)
{
    size_t rc;
    const size_t failure = (sz * nmemb) ? 0 : 1;
    size_t required_size;
    
    assert(bug2issue.curl_output_buf);

    rc = sz * nmemb;
    required_size = bug2issue.curl_store_size + rc;

    if (required_size > bug2issue.curl_alloc_size) {
        char *newbuf;
        size_t alloc_size = required_size + ALLOC_MINIMUM;

        newbuf = malloc(alloc_size);
        if (!newbuf) {
            fprintf(stderr, "curl: malloc(new_output_buf) failure.\n");
            return 0;
        }

        memcpy(newbuf, bug2issue.curl_output_buf, bug2issue.curl_store_size);
        free(bug2issue.curl_output_buf);
        bug2issue.curl_output_buf = newbuf;
        bug2issue.curl_alloc_size = alloc_size;
    }
    memcpy(bug2issue.curl_output_buf+bug2issue.curl_store_size, buffer, rc);
    bug2issue.curl_store_size += rc;
    
    return rc;
}

static int bug2issue_curl_request(const char *url, const char *requestinfo,
                                  const char *postfields)
{
    int ret;
    curl_off_t postfieldsize;
    
    if (postfields) {
        postfieldsize = strlen(postfields);
        (void)fwrite(postfields, (size_t)postfieldsize, 1, stdout);
    }

    curl_easy_setopt(bug2issue.curl, CURLOPT_URL, url);

    bug2issue.curl_store_size = 0;
    curl_easy_setopt(bug2issue.curl, CURLOPT_WRITEDATA, NULL);
    curl_easy_setopt(bug2issue.curl, CURLOPT_WRITEFUNCTION, bug2issue_curl_write_cb);

    /* insecure SSL */
    curl_easy_setopt(bug2issue.curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(bug2issue.curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(bug2issue.curl, CURLOPT_USERPWD, bug2issue.github_user);

    curl_easy_setopt(bug2issue.curl, CURLOPT_CUSTOMREQUEST, requestinfo);

    if (postfields) {
        curl_easy_setopt(bug2issue.curl, CURLOPT_POSTFIELDS, postfields);
        curl_easy_setopt(bug2issue.curl, CURLOPT_POSTFIELDSIZE_LARGE, postfieldsize);
    }

    curl_easy_setopt(bug2issue.curl, CURLOPT_HTTPHEADER, NULL);

    ret = curl_easy_perform(bug2issue.curl);
    if (ret) {
        fprintf(stderr, "curl: curl_easy_perform failure.\n");
        return ret;
    }

    (void)fwrite(bug2issue.curl_output_buf, bug2issue.curl_store_size, 1, stdout);
    return 0;
}

static int bug2issue_curl_get(const char *url)
{
    return bug2issue_curl_request(url, "GET", NULL);
}

static int bug2issue_curl_post(const char *url, const char *postfields)
{
    return bug2issue_curl_request(url, "POST", postfields);
}

static int bug2issue_curl_patch(const char *url, const char *postfields)
{
    return bug2issue_curl_request(url, "PATCH", postfields);
}

static char *bug2issue_get_issue_url(const char *url_template, const char *issue_id)
{
        char *url;
        int url_size;

        url_size = strlen(url_template) + strlen(bug2issue.github_issue_url) + strlen(issue_id);
        url = malloc(url_size);
        if (!url) {
            fprintf(stderr, "bugzilla: malloc(issue_url) failure.\n");
            return NULL;
        }
        sprintf(url, url_template, bug2issue.github_issue_url, issue_id);

        return url;
}

static char *bug2issue_get_repo_url(const char *sub)
{
    int len;
    char *url;
    char url_template[] = "https://api.github.com/repos/%s/%s";

    len = strlen(url_template) + strlen(bug2issue.github_repo) + (sub?strlen(sub):0);
    url = malloc(len);
    if (!url) {
        fprintf(stderr, "github: malloc(repo_url) failure.\n");
        return NULL;
    }
    sprintf(url, url_template, bug2issue.github_repo, sub);

    return url;
}

static int bug2issue_write_file(const char *filename, char *buf, unsigned long len)
{
    int ret;
    FILE *fp = NULL;

    fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "fopen(%s) failure.\n", filename);
        ret = -EIO;
        goto end;
    }

    (void)fwrite(buf, len, 1, fp);

end:
    if (fp)
        fclose(fp);
    return ret;
}

static int bug2issue_export_attachment(const char *comment_id, char **attach_url)
{
    int ret = 0;
    int rows;
    sql_row_t row;
    sql_len_t lens;
    json_object *object = NULL;
    const char *sql_string;
    char *alloc_string = NULL;
    int alloc_size;
    const char **column;
    char filename[MAX_PATH];
    int count;

    alloc_size = strlen(bugzilla_attach_query) + strlen(comment_id);
    alloc_string = malloc(alloc_size);
    if (!alloc_string) {
        ret = -ENOMEM;
        fprintf(stderr, "bugzilla: malloc(attach_query) failure.\n");
        goto end;
    }
    sprintf(alloc_string, bugzilla_attach_query, comment_id);
    sql_string = alloc_string;
    column = bugzilla_attach_columns;
    count = sizeof(bugzilla_attach_columns)/sizeof(const char *);

    ret = bug2issue_mysql_select(sql_string);
    if (ret) goto end;

    while (bug2issue_mysql_fetch() == 0) {
        row = bug2issue.row;
        lens = bug2issue.lens;
        if (!row || !lens) break;
        if (!row[ATT_ATT_ID_INDEX]) goto next;

        object = json_object_new_object();
        if (!object) {
            ret = -ENOMEM;
            fprintf(stderr, "json: json_object_new_object failure.\n");
            goto end;
        }

        if (bug2issue.mode & BUG2ISSUE_UPLOAD_GITHUB) {
            /* TODO: Upload to GitHub */
        } else {
            sprintf(filename, "%s\\attachment-%s-%s-%s-%s", bug2issue.issues_dir,
                    row[ATT_BUG_ID_INDEX], row[ATT_CMT_ID_INDEX],
                    row[ATT_ATT_ID_INDEX], row[ATT_FNAME_INDEX]);
            bug2issue_write_file(filename, row[ATT_CONTENT_INDEX], lens[ATT_CONTENT_INDEX]);
            *attach_url = strdup(filename);
        }

        json_object_put(object);
        object = NULL;
next:
        rows++;
    }

end:
    bug2issue_mysql_free_result();
    if (alloc_string)
        free(alloc_string);
    if (object)
        json_object_put(object);
    return ret;
}

static int bug2issue_export_comment(const char *comment_id, const char *issue_id,
                                    const char *attach_url)
{
    int ret = 0;
    int rows;
    sql_row_t row;
    json_object *object = NULL;
    const char *sql_string;
    char *alloc_string = NULL;
    int alloc_size;
    const char **column;
    int count;
    char filename[MAX_PATH];
    struct printbuf *pbuf;

    alloc_size = strlen(bugzilla_comment_query) + strlen(comment_id);
    alloc_string = malloc(alloc_size);
    if (!alloc_string) {
        ret = -ENOMEM;
        fprintf(stderr, "bugzilla: malloc(comment_query) failure.\n");
        goto end;
    }
    sprintf(alloc_string, bugzilla_comment_query, comment_id);
    sql_string = alloc_string;
    column = bugzilla_comment_columns;
    count = sizeof(bugzilla_comment_columns)/sizeof(const char *);

    ret = bug2issue_mysql_select(sql_string);
    if (ret) goto end;

    while (bug2issue_mysql_fetch() == 0) {
        row = bug2issue.row;
        if (!row) break;

        object = json_object_new_object();
        if (!object) {
            ret = -ENOMEM;
            fprintf(stderr, "json: json_object_new_object failure.\n");
            goto end;
        }

        pbuf = printbuf_new();
        if (!pbuf) {
            ret = -ENOMEM;
            fprintf(stderr, "json: printbuf_new failure.\n");
            goto end;
        }

        if (bug2issue.mode & BUG2ISSUE_EXPORT_ATTACHMENT && row[CMT_ATT_ID_INDEX]) {
            sprintbuf(pbuf,
                      "Commented by: %s <%s>\n"
                      "Commented at: %s\n"
                      "\n"
                      "%s\n"
                      "\n"
                      "Attachment Name: %s\n"
                      "Attachment MIME: %s\n"
                      "Attachment Description: %s\n"
                      "Attachment URL: %s\n",
                      row[CMT_CNAME_INDEX], row[CMT_EMAIL_INDEX],
                      row[CMT_CREATE_INDEX],
                      row[CMT_TEXT_INDEX],
                      row[CMT_ATT_NAME_INDEX],
                      row[CMT_ATT_MIME_INDEX],
                      row[CMT_ATT_DESC_INDEX],
                      attach_url);
        } else {
            sprintbuf(pbuf,
                      "Commented by: %s <%s>\n"
                      "Commented at: %s\n"
                      "\n"
                      "%s\n",
                      row[CMT_CNAME_INDEX], row[CMT_EMAIL_INDEX],
                      row[CMT_CREATE_INDEX],
                      row[CMT_TEXT_INDEX]);
        }
        json_object_object_add(object, "body", json_object_new_string(pbuf->buf));

        printbuf_free(pbuf);

        if (bug2issue.mode & BUG2ISSUE_UPLOAD_GITHUB) {
            char *url;

            url = bug2issue_get_issue_url("%s/%s/comments", issue_id);
            if (!url) {
                ret = -ENOMEM;
                goto end;
            }
            ret = bug2issue_curl_post(url, json_object_to_json_string(object));
            free(url);
        } else {
            sprintf(filename, "%s\\comment-%s-%s.json", bug2issue.issues_dir, row[0], row[1]);
            json_object_to_file(filename, object);
        }

        json_object_put(object);
        object = NULL;
        rows++;
    }

end:
    bug2issue_mysql_free_result();
    if (alloc_string)
        free(alloc_string);
    if (object)
        json_object_put(object);
    return ret;
}

static int bug2issue_list_comments(const char *bug_id)
{
    int ret = 0;
    int rows;
    int index;
    sql_row_t row;
    json_object *object = NULL;
    const char *sql_string;
    char *alloc_string = NULL;
    int alloc_size;
    int count;

    assert(!bug2issue.comments);

    alloc_size = strlen(bugzilla_comments_query) + strlen(bug_id);
    alloc_string = malloc(alloc_size);
    if (!alloc_string) {
        ret = -ENOMEM;
        fprintf(stderr, "bugzilla: malloc(comments_query) failure.\n");
        goto end;
    }
    sprintf(alloc_string, bugzilla_comments_query, bug_id);
    sql_string = alloc_string;

    count = 1;

    object = json_object_new_array();
    if (!object) {
        ret = -ENOMEM;
        fprintf(stderr, "json: json_object_new_object failure.\n");
        goto end;
    }

    ret = bug2issue_mysql_select(sql_string);
    if (ret) goto end;

    while (bug2issue_mysql_fetch() == 0) {
        row = bug2issue.row;
        if (!row) break;

        for (index = 0; index < count; index++) {
            if (row[0])
                json_object_array_add(object, json_object_new_string(row[0]));
        }
        rows++;
	}

    bug2issue.comments = object;
    object = NULL;

end:
	bug2issue_mysql_free_result();
    if (object)
        json_object_put(object);
    if (alloc_string)
        free(alloc_string);
    return ret;
}

static void bug2issue_export_comments(const char *bug_id, const char *issue_id)
{
    int ret;
    const char *comment_id;
    int nr_comments, idx;
    char *attach_url = NULL;

    do {
        ret = bug2issue_list_comments(bug_id);
    } while (ret);

    assert(bug2issue.comments);

    nr_comments = json_object_array_length(bug2issue.comments);
    for (idx = 0; idx < nr_comments; idx++) {
        comment_id = json_object_get_string(json_object_array_get_idx(bug2issue.comments, idx));
        if (bug2issue.mode & BUG2ISSUE_EXPORT_ATTACHMENT) {
            do {
                ret = bug2issue_export_attachment(comment_id, &attach_url);
            } while (ret);
        }
        do {
            ret = bug2issue_export_comment(comment_id, issue_id, attach_url);
        } while (ret);
        if (attach_url) {
            free(attach_url);
            attach_url = NULL;
        }
    }

    json_object_put(bug2issue.comments);
    bug2issue.comments = NULL;
}

static int bug2issue_is_valid_label(const char *label)
{
    return label && strlen(label);
}

static int bug2issue_create_issue(const char *bug_id, char **issue_id, int *closed)
{
    int ret = 0;
    int rows;
    sql_row_t row;
    json_object *object = NULL;
    const char *sql_string;
    char *alloc_string = NULL;
    int alloc_size;
    const char **column;
    int count;
    char filename[MAX_PATH];
    struct printbuf *pbuf;
    json_object *result;
    json_object *labels;
    json_object *issue_id_obj;

    assert(bug_id);

    alloc_size = strlen(bugzilla_issue_query) + strlen(bug_id);
    alloc_string = malloc(alloc_size);
    if (!alloc_string) {
        ret = -ENOMEM;
        fprintf(stderr, "bugzilla: malloc(issue_query) failure.\n");
        goto end;
    }
    sprintf(alloc_string, bugzilla_issue_query, bug_id);
    sql_string = alloc_string;

    column = bugzilla_issue_columns;
    count = sizeof(bugzilla_issue_columns)/sizeof(const char *);

    ret = bug2issue_mysql_select(sql_string);
    if (ret) goto end;

    while (bug2issue_mysql_fetch() == 0) {
        row = bug2issue.row;
        if (!row) break;

        object = json_object_new_object();
        if (!object) {
            ret = -ENOMEM;
            fprintf(stderr, "json: json_object_new_object failure.\n");
            goto end;
        }

        if (bug2issue.mode & (BUG2ISSUE_LABEL_FIELD | BUG2ISSUE_LABEL_COMPONENT)) {
            labels = json_object_new_array();
            if (!labels) {
                ret = -ENOMEM;
                fprintf(stderr, "json: json_object_new_array failure.\n");
                goto end;
            }
            json_object_object_add(object, "labels", labels);
        }

        pbuf = printbuf_new();
        if (!pbuf) {
            ret = -ENOMEM;
            fprintf(stderr, "json: printbuf_new failure.\n");
            goto end;
        }

        if (bug2issue.mode & BUG2ISSUE_TITLE_BUGIDS)
            sprintbuf(pbuf, "Bug %s - %s", row[BUG_ID_INDEX], row[BUG_TITLE_INDEX]);
        else
            sprintbuf(pbuf, "%s", row[BUG_TITLE_INDEX]);
        json_object_object_add(object, "title", json_object_new_string(pbuf->buf));

        printbuf_reset(pbuf);

        sprintbuf(pbuf,
                  "Reported by: %s <%s>\n"
                  "Reported at: %s\n"
                  "\n"
                  "Product: %s\n"
                  "Component: %s\n"
                  "Platform: %s\n"
                  "OS: %s\n"
                  "Priority: %s\n"
                  "Severity: %s\n",
                  row[BUG_CNAME_INDEX], row[BUG_EMAIL_INDEX],
                  row[BUG_CREATE_INDEX],
                  row[BUG_PRODUCT_INDEX],
                  row[BUG_COMPONENT_INDEX],
                  row[BUG_PLATFORM_INDEX],
                  row[BUG_OS_INDEX],
                  row[BUG_PRIORITY_INDEX],
                  row[BUG_SEVERITY_INDEX]);
        json_object_object_add(object, "body", json_object_new_string(pbuf->buf));

        printbuf_free(pbuf);

        if (bug2issue_is_closed_bug(row[BUG_STATUS_INDEX])) {
            *closed = 1;
            json_object_object_add(object, "state", json_object_new_string("closed"));
        } else {
            *closed = 0;
            json_object_object_add(object, "state", json_object_new_string("open"));
        }

        if (bug2issue.mode & BUG2ISSUE_LABEL_FIELD) {
            if (bug2issue_is_labeled_field("rep_platform") &&
                bug2issue_is_valid_label(row[BUG_PLATFORM_INDEX]))
               json_object_array_add(labels, json_object_new_string(row[BUG_PLATFORM_INDEX]));
            if (bug2issue_is_labeled_field("op_sys") &&
                bug2issue_is_valid_label(row[BUG_OS_INDEX]))
               json_object_array_add(labels, json_object_new_string(row[BUG_OS_INDEX]));
            if (bug2issue_is_labeled_field("priority") &&
                bug2issue_is_valid_label(row[BUG_PRIORITY_INDEX]))
               json_object_array_add(labels, json_object_new_string(row[BUG_PRIORITY_INDEX]));
            if (bug2issue_is_labeled_field("bug_severity") &&
                bug2issue_is_valid_label(row[BUG_SEVERITY_INDEX]))
               json_object_array_add(labels, json_object_new_string(row[BUG_SEVERITY_INDEX]));
            if (bug2issue_is_labeled_field("bug_status") &&
                bug2issue_is_valid_label(row[BUG_STATUS_INDEX]))
               json_object_array_add(labels, json_object_new_string(row[BUG_STATUS_INDEX]));
            if (bug2issue_is_labeled_field("resolution") &&
                bug2issue_is_valid_label(row[BUG_RESOLUTION_INDEX]))
               json_object_array_add(labels, json_object_new_string(row[BUG_RESOLUTION_INDEX]));
        }
        if (bug2issue.mode & BUG2ISSUE_LABEL_COMPONENT) {
            if (bug2issue_is_valid_label(row[BUG_COMPONENT_INDEX]))
               json_object_array_add(labels, json_object_new_string(row[BUG_COMPONENT_INDEX]));
        }

        if (bug2issue.mode & BUG2ISSUE_UPLOAD_GITHUB) {
            ret = bug2issue_curl_post(bug2issue.github_issue_url,
                                      json_object_to_json_string(object));
            if (ret)
                goto end;

            result = json_tokener_parse(bug2issue.curl_output_buf);
            if (!result) {
                ret = -EINVAL;
                fprintf(stderr, "json: json_tokener_parse failure.\n");
                goto end;
            }

            issue_id_obj = json_object_object_get(result, "number");
            if (!issue_id_obj) {
                ret = -EINVAL;
                json_object_put(result);
                fprintf(stderr, "github: no issue_id found.\n");
                goto end;
            }
            *issue_id = strdup(json_object_get_string(issue_id_obj));
            json_object_put(result);
        } else {
            sprintf(filename, "%s\\issue-%s.json", bug2issue.issues_dir, row[0]);
            json_object_to_file(filename, object);
        }

        json_object_put(object);
        object = NULL;
        rows++;
    }

end:
	bug2issue_mysql_free_result();
    if (alloc_string)
        free(alloc_string);
    if (object)
        json_object_put(object);
    return ret;
}

int bug2issue_close_issue(const char *issue_id)
{
    int ret = 0;
    char *url = NULL;
    json_object *object = NULL;

    url = bug2issue_get_issue_url("%s/%s", issue_id);
    if (!url) {
        ret = -ENOMEM;
        goto end;
    }

    object = json_object_new_object();
    if (!object) {
        ret = -ENOMEM;
        fprintf(stderr, "json: json_object_new_object failure.\n");
        goto end;
    }

    json_object_object_add(object, "state", json_object_new_string("closed"));
    if (bug2issue.mode & BUG2ISSUE_UPLOAD_GITHUB) {
        ret = bug2issue_curl_patch(url, json_object_to_json_string(object));
        if (ret)
            goto end;
    }

end:
    if (url)
        free(url);
    if (object)
        json_object_put(object);
    return ret;
}

static void bug2issue_export_issue(const char *bug_id)
{
    int ret = 0;
    char *issue_id = NULL;

    if (bug2issue.mode & BUG2ISSUE_EXPORT_ISSUE) {
        int closed;

        do {
            ret = bug2issue_create_issue(bug_id, &issue_id, &closed);
        } while (ret);

        if (bug2issue.mode & BUG2ISSUE_EXPORT_COMMENT)
            bug2issue_export_comments(bug_id, issue_id);

        if (closed && bug2issue.mode & BUG2ISSUE_UPLOAD_GITHUB) {
            do {
                ret = bug2issue_close_issue(issue_id);
            } while (0);
        }
    }

    if (issue_id)
        free(issue_id);
}

static int bug2issue_list_issues(void)
{
    int ret = 0;
    int rows;
    int index;
    sql_row_t row;
    json_object *object = NULL;
    const char *sql_string;
    int count;

    assert(!bug2issue.bugs);

    sql_string = bugzilla_issues_query;
    count = 1;

    object = json_object_new_array();
    if (!object) {
        ret = -ENOMEM;
        fprintf(stderr, "json: json_object_new_object failure.\n");
        goto end;
    }

    ret = bug2issue_mysql_select(sql_string);
    if (ret) goto end;

    while (bug2issue_mysql_fetch() == 0) {
        row = bug2issue.row;
        if (!row) break;

        for (index = 0; index < count; index++) {
            if (row[0]) {
                json_object_array_add(object, json_object_new_string(row[0]));
                if (bug2issue.mode & BUG2ISSUE_LIST_BUGID)
                    fprintf(stdout, "%s\n", row[0]);
            }
        }
        rows++;
	}

    bug2issue.bugs = object;
    object = NULL;

end:
	bug2issue_mysql_free_result();
    if (object)
        json_object_put(object);
    return ret;
}

static void bug2issue_export_issues(void)
{
    int ret;
    const char *bug_id;
    int nr_bugs, idx;

    if (bug2issue.bug_id) {
        bug2issue_export_issue(bug2issue.bug_id);
        return;
    } else {
        do {
            ret = bug2issue_list_issues();
        } while (ret);
    }

    assert(bug2issue.bugs);

    nr_bugs = json_object_array_length(bug2issue.bugs);
    for (idx = 0; idx < nr_bugs; idx++) {
        bug_id = json_object_get_string(json_object_array_get_idx(bug2issue.bugs, idx));
        bug2issue_export_issue(bug_id);
    }
}

static int bug2issue_list_labels(void)
{
    int ret = 0;
    json_object *result = NULL, *label;
    int nr_labels, idx;

    ret = bug2issue_curl_get(bug2issue.github_label_url);
    if (ret) return ret;

    result = json_tokener_parse(bug2issue.curl_output_buf);
    if (!result) {
        ret = -EINVAL;
        fprintf(stderr, "json: json_tokener_parse failure.\n");
        goto end;
    }
    nr_labels = json_object_array_length(result);
    for (idx = 0; idx < nr_labels; idx++) {
        label = json_object_object_get(json_object_array_get_idx(result, idx), "name");
        if (label)
            array_list_add(bug2issue.exist_labels, strdup(json_object_get_string(label)));
    }

end:
    if (result)
        json_object_put(result);
    return 0;
}

static int bug2issue_export_field(const char *field, const char *color)
{
    int ret = 0;
    int rows;
    sql_row_t row;
    json_object *object = NULL;
    const char *sql_string;
    char *alloc_string = NULL;
    int alloc_size;

    assert(field);

    alloc_size = strlen(bugzilla_field_query) + strlen(field);
    alloc_string = malloc(alloc_size);
    if (!alloc_string) {
        ret = -ENOMEM;
        fprintf(stderr, "bugzilla: malloc(field_query) failure.\n");
        goto end;
    }
    sprintf(alloc_string, bugzilla_field_query, field);
    sql_string = alloc_string;

    ret = bug2issue_mysql_select(sql_string);
    if (ret) goto end;

    while (bug2issue_mysql_fetch() == 0) {
        row = bug2issue.row;
        if (!row) break;

        if (!row[0] || !strlen(row[0]) || bug2issue_is_exist_label(row[0]))
            goto next;

        object = json_object_new_object();
        if (!object) {
            ret = -ENOMEM;
            fprintf(stderr, "json: json_object_new_object failure.\n");
            goto end;
        }

        json_object_object_add(object, "name", json_object_new_string(row[0]));
        json_object_object_add(object, "color", json_object_new_string(color));

        ret = bug2issue_curl_post(bug2issue.github_label_url,
                                  json_object_to_json_string(object));
        if (ret) goto end;

        json_object_put(object);
        object = NULL;

next:
        rows++;
    }

end:
	bug2issue_mysql_free_result();
    if (alloc_string)
        free(alloc_string);
    if (object)
        json_object_put(object);
    return ret;
}

static int bug2issue_export_component(const char *product)
{
    int ret = 0;
    int rows;
    sql_row_t row;
    json_object *object = NULL;
    const char *sql_string;
    char *alloc_string = NULL;
    int alloc_size;

    assert(product);

    alloc_size = strlen(bugzilla_component_query) + strlen(product);
    alloc_string = malloc(alloc_size);
    if (!alloc_string) {
        ret = -ENOMEM;
        fprintf(stderr, "bugzilla: malloc(component_query) failure.\n");
        goto end;
    }
    sprintf(alloc_string, bugzilla_component_query, product);
    sql_string = alloc_string;

    ret = bug2issue_mysql_select(sql_string);
    if (ret) goto end;

    while (bug2issue_mysql_fetch() == 0) {
        row = bug2issue.row;
        if (!row) break;

        if (!row[2] || bug2issue_is_exist_label(row[2]))
            goto next;

        object = json_object_new_object();
        if (!object) {
            ret = -ENOMEM;
            fprintf(stderr, "json: json_object_new_object failure.\n");
            goto end;
        }

        json_object_object_add(object, "name", json_object_new_string(row[2]));
        json_object_object_add(object, "color", json_object_new_string(github_label_colors[0]));

        ret = bug2issue_curl_post(bug2issue.github_label_url,
                                  json_object_to_json_string(object));
        if (ret) goto end;

        json_object_put(object);
        object = NULL;

next:
        rows++;
    }

end:
	bug2issue_mysql_free_result();
    if (alloc_string)
        free(alloc_string);
    if (object)
        json_object_put(object);
    return ret;
}

static int bug2issue_export_labels(void)
{
    int ret;
    int idx;
    const char *iter;

    /* only available in migrate mode */
    if (!(bug2issue.mode & BUG2ISSUE_UPLOAD_GITHUB))
        return 0;

    ret = bug2issue_list_labels();
    if (ret) return ret;

    if (bug2issue.mode & BUG2ISSUE_LABEL_FIELD) {
        foreach_array(idx, github_label_fields, iter) {
            if (bug2issue_is_labeled_field(iter)) {
                ret = bug2issue_export_field(iter, github_label_colors[idx+1]);
                if (ret) return ret;
            }
        }
    }
    
    if (bug2issue.mode & BUG2ISSUE_LABEL_COMPONENT) {
        ret = bug2issue_export_component(bug2issue.bugzilla_product);
        if (ret) return ret;
    }

    return 0;
}

#ifndef HAVE_LOCALTIME_R
struct tm *localtime_r(const time_t *l_clock, struct tm *result)
{
    memcpy(result, localtime(l_clock), sizeof(*result));
    return result;
}
#endif

static int bug2issue_split_colon(const char *string,
                                 char const **param1, char const **param2)
{
    char *pos;
    
    assert(param1 && param2);

    pos = strchr(string, ':');
    if (!pos) {
        *param1 = string;
        return 0;
    }

    *pos = 0;
    *param1 = string;
    *param2 = pos+1;

    return 0;
}

static int bug2issue_init(void)
{
    static char cwd[MAX_PATH];

    memset(&bug2issue, 0, sizeof(struct bug2issue_cfg));

    /* default mode */
    bug2issue.mode = (BUG2ISSUE_UPLOAD_GITHUB | BUG2ISSUE_EXPORT_ISSUE);

    bug2issue.sql_server = "localhost";
    bug2issue.sql_port = "3306";
    bug2issue.sql_db = "bugzilla";
    bug2issue.sql_login = "root";
    bug2issue.sql_password = "secret";

    /* dump folder */
    bug2issue.issues_dir = getcwd(cwd, MAX_PATH);

    bug2issue.github_repo = "zetalog/bug2issue";
    bug2issue.github_user = "zetalog:secret";

    bug2issue.curl_output_buf = malloc(ALLOC_MINIMUM);
    if (!bug2issue.curl_output_buf) {
        fprintf(stderr, "curl: malloc(output_buf) failure.\n");
        return -ENOMEM;
    }

    bug2issue.close_states = array_list_new(&bug2issue_json_free_dummy);
    if (!bug2issue.close_states) {
        fprintf(stderr, "curl: array_list_new(close_states) failure.\n");
        return -ENOMEM;
    }

    bug2issue.field_labels = array_list_new(&bug2issue_json_free_dummy);
    if (!bug2issue.field_labels) {
        fprintf(stderr, "curl: array_list_new(field_labels) failure.\n");
        return -ENOMEM;
    }

    bug2issue.exist_labels = array_list_new(&free);
    if (!bug2issue.exist_labels) {
        fprintf(stderr, "curl: array_list_new(exist_labels) failure.\n");
        return -ENOMEM;
    }

    return 0;
}

static void bug2issue_exit(void)
{
    if (bug2issue.close_states)
        array_list_free(bug2issue.close_states);
    if (bug2issue.field_labels)
        array_list_free(bug2issue.field_labels);
    if (bug2issue.exist_labels)
        array_list_free(bug2issue.exist_labels);
    if (bug2issue.curl_output_buf)
        free(bug2issue.curl_output_buf);
}

static int bug2issue_start(void)
{
    int ret;
    CURLcode code;

    if (bug2issue_curl_required()) {
        code = curl_global_init(CURL_GLOBAL_DEFAULT);
        if (code != CURLE_OK) {
            fprintf(stderr, "curl: curl_global_init failure.\n");
            return -ENOMEM;
        }

        bug2issue.curl = curl_easy_init();
        if (!bug2issue.curl) {
            fprintf(stderr, "curl: curl_easy_init failure.\n");
            return -ENOMEM;
        }

        bug2issue.github_issue_url = bug2issue_get_repo_url("issues");
        if (!bug2issue.github_issue_url)
            return -ENOMEM;

        bug2issue.github_label_url = bug2issue_get_repo_url("labels");
        if (!bug2issue.github_label_url)
            return -ENOMEM;

        curl_easy_setopt(bug2issue.curl, CURLOPT_USERAGENT, CURL_USERAGENT);
    }

    ret = bug2issue_mysql_init();
    if (ret) return ret;

    return 0;
}

static void bug2issue_stop(void)
{
    bug2issue_mysql_exit();

    if (bug2issue_curl_required()) {
        if (bug2issue.curl)
            curl_easy_cleanup(bug2issue.curl);

        curl_global_cleanup();

        if (bug2issue.github_issue_url) {
            free(bug2issue.github_issue_url);
            bug2issue.github_issue_url = NULL;
        }

        if (bug2issue.github_label_url) {
            free(bug2issue.github_label_url);
            bug2issue.github_label_url = NULL;
        }
    }
}

static struct option long_options[] = {
    { "bug", 1, 0, 'b' },
    { "list-bugids", 0, 0, 'i' },
    { "export-folder", 1, 0, 'f' },
    { "comments", 0, 0, 'c' },
    { "attachments", 0, 0, 'a' },
    { "bugzilla-host", 1, 0, 'h' },
    { "bugzilla-user", 1, 0, 'u' },
    { "bugzilla-db", 1, 0, 'd' },
    { "github-repo", 1, 0, 'r' },
    { "github-user", 1, 0, 'w' },
    { "close-status", 1, 0, 's' },
    { "field-label", 1, 0, 'l' },
    { "component-label", 1, 0, 'n' },
    { "bugids-title", 0, 0, 't' },
    { 0, 0, 0, 0 }
};

static void usage(void)
{
    fprintf(stdout, "Usage bug2issue\n");
    fprintf(stdout, "  [-i|--list-bugids]\n");
    fprintf(stdout, "  [-f|--export-folder]\n");
    fprintf(stdout, "  [-c|--comments]\n");
    fprintf(stdout, "  [-a|--attachments]\n");
    fprintf(stdout, "  [-b|--bug bug_id] dir\n");
    fprintf(stdout, "  [-d|--bugzilla-db database]\n");
    fprintf(stdout, "  [-h|--bugzilla-host host[:port]]\n");
    fprintf(stdout, "  [-u|--bugzilla-user user[:pass]]\n");
    fprintf(stdout, "  [-r|--github-repo repository]\n");
    fprintf(stdout, "  [-w|--github-user user[:pass]]\n");
    fprintf(stdout, "  [-s|--close-status status\n");
    fprintf(stdout, "  [-l|--field-label field]\n");
    fprintf(stdout, "  [-n|--component-label product]\n");
    fprintf(stdout, "  [-t|--bugids-title]\n");
    fprintf(stdout, "This program has following modes:\n");
    fprintf(stdout, " migrate: Migrate bugzilla bugs to github issues (default mode)\n");
    fprintf(stdout, " list   : List bugzilla bug IDs\n");
    fprintf(stdout, " export : Export bugzilla bugs to github IssueAPI compliant json files\n");
    fprintf(stdout, "This program has following options:\n");
    fprintf(stdout, " -i, --list-bugids\n");
    fprintf(stdout, "   disable 'export/migrate' modes, enable 'list' mode\n");
    fprintf(stdout, " -f, --export-folder\n");
    fprintf(stdout, "   disable 'migrate' mode, enable 'export' mode if 'list' mode is disabled\n");
    fprintf(stdout, "   specify local folder to store json files\n");
    fprintf(stdout, " -c, --comments\n");
    fprintf(stdout, "   used in 'export/migrate' modes\n");
    fprintf(stdout, "   export/migrate comments along with the issues\n");
    fprintf(stdout, " -a, --attachments\n");
    fprintf(stdout, "   used in 'export/migrate' modes\n");
    fprintf(stdout, "   export/migrate attachments along with the issues/comments\n");
    fprintf(stdout, " -b, --bug\n");
    fprintf(stdout, "   used in 'export/migrate' mode\n");
    fprintf(stdout, "   export specified bug in 'export/migrate' modes\n");
    fprintf(stdout, " -d, --bugzilla-db\n");
    fprintf(stdout, "   used in 'list/export/migrate' modes\n");
    fprintf(stdout, "   specify bugzilla mysql database name, default is 'bugzilla'\n");
    fprintf(stdout, " -h, --bugzilla-host\n");
    fprintf(stdout, "   used in 'list/export/migrate' modes\n");
    fprintf(stdout, "   specify bugzilla mysql database host:port, default is 'localhost:3306'\n");
    fprintf(stdout, " -u, --bugzilla-user\n");
    fprintf(stdout, "   used in 'list/export/migrate' modes\n");
    fprintf(stdout, "   specify bugzilla mysql database user:password, default is 'root:secret'\n");
    fprintf(stdout, " -r, --github-repo\n");
    fprintf(stdout, "   used in 'migrate' mode\n");
    fprintf(stdout, "   specify github repo name, default is 'zetalog/bug2issue'\n");
    fprintf(stdout, " -w, --github-user\n");
    fprintf(stdout, "   used in 'migrate' mode\n");
    fprintf(stdout, "   specify github user:password, default is 'zetalog:secret'\n");
    fprintf(stdout, " -s, --close-status\n");
    fprintf(stdout, "   used in 'export/migrate' modes\n");
    fprintf(stdout, "   multiple specify bug status (ex. CLOSED) that can be treated as close\n");
    fprintf(stdout, " -l, --field-label\n");
    fprintf(stdout, "   used in 'export/migrate' modes\n");
    fprintf(stdout, "   multiple specify bug fields to be converted into issue label\n");
    fprintf(stdout, "   Following fields are possible:\n");
    fprintf(stdout, "    rep_platform op_sys priority bug_severity bug_status resolution\n");
    fprintf(stdout, " -n, --component-label\n");
    fprintf(stdout, "   used in 'export/migrate' modes\n");
    fprintf(stdout, "   specify product to convert its component into issue label\n");
    fprintf(stdout, " -t, --bugids-title\n");
    fprintf(stdout, "   used in 'export/migrate' modes\n");
    fprintf(stdout, "   add bugid into issue's title\n");

    exit(-1);
}

int main(int argc, char **argv)
{
    char c;
    int ret = 0;

    ret = bug2issue_init();
    if (ret)
        exit(-1);
    
    while (1) {
        int option_index = 0;

        c = getopt_long(argc, argv, "if:cab:d:h:u:r:w:s:l:n:t", long_options, &option_index);
        if (c == EOF)
            break;

        switch (c) {
        case 'i':
            bug2issue.mode |= BUG2ISSUE_LIST_BUGID;
            break;
        case 'f':
            bug2issue.mode &= ~BUG2ISSUE_UPLOAD_GITHUB;
            bug2issue.issues_dir = optarg;
            break;
        case 'c':
            bug2issue.mode |= (BUG2ISSUE_EXPORT_ISSUE | BUG2ISSUE_EXPORT_COMMENT);
            break;
        case 'a':
            bug2issue.mode |= (BUG2ISSUE_EXPORT_ISSUE | \
                               BUG2ISSUE_EXPORT_COMMENT | \
                               BUG2ISSUE_EXPORT_ATTACHMENT);
            break;
        case 'b':
            bug2issue.bug_id = optarg;
            break;
        case 'd':
            bug2issue.sql_db = optarg;
            break;
        case 'h':
            bug2issue_split_colon(optarg, &bug2issue.sql_server, &bug2issue.sql_port);
            break;
        case 'u':
            bug2issue_split_colon(optarg, &bug2issue.sql_login, &bug2issue.sql_password);
            break;
        case 'r':
            bug2issue.github_repo = optarg;
            break;
        case 'w':
            bug2issue.github_user = optarg;
            break;
        case 's':
            bug2issue_add_close_status(optarg);
            break;
        case 'l':
            if (bug2issue_add_field_label(optarg))
                usage();
            break;
        case 'n':
            bug2issue.bugzilla_product = optarg;
            bug2issue.mode |= BUG2ISSUE_LABEL_COMPONENT;
            break;
        case 't':
            bug2issue.mode |= BUG2ISSUE_TITLE_BUGIDS;
            break;
        default:
            usage();
            break;
        }
    }
    argc -= optind;
    argv += optind;

    ret = bug2issue_start();
    if (ret)
        exit(-1);

    /* This mode will prevent export/migration from being executed. */
    if (bug2issue.mode & BUG2ISSUE_LIST_BUGID) {
        bug2issue.mode = BUG2ISSUE_LIST_BUGID;
        bug2issue.bug_id = NULL;
    }

    bug2issue_export_labels();
    bug2issue_export_issues();

    bug2issue_stop();
    bug2issue_exit();

    return ret;
}
