#ifdef WIN32
#include <winsock.h>
#include <direct.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <getopt.h>
#include <json.h>
#include <mysql.h>
#include <errmsg.h>

#define SQL_DOWN			1 /* for re-connect */

typedef char **sql_row_t;

struct mysql_conn {
    MYSQL conn;
    MYSQL *sock;
    MYSQL_RES *result;
    sql_row_t row;
};

struct bug2issue_cfg {
    char *sql_server;
    char *sql_port;
    char *sql_login;
    char *sql_password;
    char *sql_db;
    struct mysql_conn *conn;
    sql_row_t row;

    char *issues_dir;
    char *bug_id;
    int mode;
#define BUG2ISSUE_EXPORT_ISSUE      0
#define BUG2ISSUE_EXPORT_COMMENT    1
};

struct bug2issue_cfg bug2issue;

const char *bugzilla_bug_query = "select "
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
    "order by bugs.bug_id;";
const char *bugzilla_bug_columns[] = {
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

const char *bugzilla_comment_all_query = "select "
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
    "order by longdescs.bug_id;";
const char *bugzilla_comment_one_query = "select "
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
    "where longdescs.bug_id=%s "
    "order by longdescs.bug_id;";
const char *bugzilla_comment_columns[] = {
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

static int bug2issue_mysql_init(struct bug2issue_cfg *config)
{
    int ret = 0;
    struct mysql_conn *mysql_sock;

    if (!config->conn) {
        mysql_sock = (struct mysql_conn *)malloc(sizeof(struct mysql_conn));
        if (!mysql_sock) {
            fprintf(stderr, "mysql: malloc failure.\n");
            return -1;
        }
        memset(mysql_sock, 0, sizeof(*mysql_sock));

        mysql_init(&(mysql_sock->conn));
        mysql_options(&(mysql_sock->conn), MYSQL_READ_DEFAULT_GROUP, config->sql_db);
        mysql_sock->sock = mysql_real_connect(&(mysql_sock->conn),
                                              config->sql_server,
                                              config->sql_login,
                                              config->sql_password,
                                              config->sql_db,
                                              atoi(config->sql_port),
                                              NULL,
                                              CLIENT_FOUND_ROWS);
        if (mysql_sock->sock)
            config->conn = mysql_sock;
        else {
            fprintf(stderr, "mysql: mysql_real_connect failure.\n");
            fprintf(stderr, "mysql: username@host:database - %s@%s:%s\n",
                    config->sql_login, config->sql_server, config->sql_db);
            ret = bug2issue_mysql_error(mysql_errno(&mysql_sock->conn),
                                        mysql_error(&mysql_sock->conn));
            mysql_sock->sock = NULL;
        }
    }

    return ret;
}

static void bug2issue_mysql_free_result(struct bug2issue_cfg *config)
{
    struct mysql_conn *mysql_sock = config->conn;

    if (mysql_sock->result) {
        mysql_free_result(mysql_sock->result);
        mysql_sock->result = NULL;
    }
}

static int bug2issue_mysql_query(struct bug2issue_cfg *config,
                                 const char *querystr)
{
    struct mysql_conn *mysql_sock = config->conn;
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

static int bug2issue_mysql_store_result(struct bug2issue_cfg *config)
{
    struct mysql_conn *mysql_sock = config->conn;
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

static int bug2issue_mysql_num_fields(struct bug2issue_cfg *config)
{
    int num = 0;
    struct mysql_conn *mysql_sock = config->conn;

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

static int bug2issue_mysql_select(struct bug2issue_cfg *config,
                                  const char *querystr)
{
    int ret;

    ret = bug2issue_mysql_query(config, querystr);
    if (ret) return ret;
    ret = bug2issue_mysql_store_result(config);
    if (ret) return ret;
    bug2issue_mysql_num_fields(config);

    return ret;
}

static int bug2issue_mysql_fetch(struct bug2issue_cfg *config)
{
    int ret = 0;
    struct mysql_conn *mysql_sock = config->conn;

    if (!mysql_sock->result)
        return SQL_DOWN;

    config->row = mysql_fetch_row(mysql_sock->result);
    if (config->row == NULL)
        ret = bug2issue_mysql_error(mysql_errno(mysql_sock->sock),
                                    mysql_error(mysql_sock->sock));

    return ret;
}

int bug2issue_export_issues(struct bug2issue_cfg *config)
{
    int ret = 0;
    int rows;
    int index;
    sql_row_t row;
    json_object *object = NULL;
    const char *sql_string;
    const char **column;
    int count;
    char filename[MAX_PATH];

    sql_string = bugzilla_bug_query;
    column = bugzilla_bug_columns;
    count = sizeof(bugzilla_bug_columns)/sizeof(const char *);

    ret = bug2issue_mysql_init(config);
    if (ret) return ret;
	ret = bug2issue_mysql_select(config, sql_string);
    if (ret) goto end;

    while (bug2issue_mysql_fetch(config) == 0) {
		row = config->row;
		if (!row) break;

        object = json_object_new_object();
        if (!object) {
            ret = -1;
            fprintf(stderr, "json: json_object_new_object failure.\n");
            goto end;
        }

        /* TODO: GitHub Issue Format
         *
         * Following codes may be modified according to github issue format.
         */
		for (index = 0; index < count; index++) {
            if (row[index])
                json_object_object_add(object, column[index],
                                       json_object_new_string(row[index]));
		}
        sprintf(filename, "%s\\issue-%s.json", config->issues_dir, row[0]);
        json_object_to_file(filename, object);

        /* TODO: Upload GitHub Issue */

        json_object_put(object);
        object = NULL;
		rows++;
	}

end:
	bug2issue_mysql_free_result(config);
    if (object)
        json_object_put(object);
    return ret;
}

int bug2issue_export_comments(struct bug2issue_cfg *config)
{
    int ret = 0;
    int rows;
    int index;
    sql_row_t row;
    json_object *object = NULL;
    const char *sql_string;
    char *alloc_string = NULL;
    int alloc_size;
    const char **column;
    int count;
    char filename[MAX_PATH];

    if (!config->bug_id) {
        sql_string = bugzilla_comment_all_query;
    } else {
        alloc_size = strlen(bugzilla_comment_one_query) + strlen(config->bug_id);
        alloc_string = malloc(alloc_size);
        if (!alloc_string) {
            ret = -1;
            fprintf(stderr, "json: malloc failure.\n");
            goto end;
        }
        sprintf(alloc_string, bugzilla_comment_one_query, config->bug_id);
        sql_string = alloc_string;
    }
    column = bugzilla_comment_columns;
    count = sizeof(bugzilla_comment_columns)/sizeof(const char *);

    ret = bug2issue_mysql_init(config);
    if (ret) return ret;
	ret = bug2issue_mysql_select(config, sql_string);
    if (ret) goto end;

    while (bug2issue_mysql_fetch(config) == 0) {
		row = config->row;
		if (!row) break;

        object = json_object_new_object();
        if (!object) {
            ret = -1;
          fprintf(stderr, "json: json_object_new_object failure.\n");
            goto end;
        }

        /* TODO: GitHub Comment Format
         *
         * Following codes may be modified according to github comment format.
         * There's still no APIs for github issues' attachment support.
         */
		for (index = 0; index < count; index++) {
            if (row[index])
                json_object_object_add(object, column[index],
                                       json_object_new_string(row[index]));
		}
        sprintf(filename, "%s\\comment-%s-%s.json", config->issues_dir, row[0], row[1]);
        json_object_to_file(filename, object);

        /* TODO: upload github comment here */

        json_object_put(object);
        object = NULL;
		rows++;
	}

end:
	bug2issue_mysql_free_result(config);
    if (alloc_string)
        free(alloc_string);
    if (object)
        json_object_put(object);
    return ret;
}

#ifndef HAVE_LOCALTIME_R
struct tm *localtime_r(const time_t *l_clock, struct tm *result)
{
    memcpy(result, localtime(l_clock), sizeof(*result));
    return result;
}
#endif

static struct option long_options[] = {
    { "bug", 1, 0, 'b' },
    { "comment", 0, 0, 'c' },
    { "host", 1, 0, 'h' },
    { "port", 1, 0, 'p' },
    { "database", 1, 0, 'd' },
    { "username", 1, 0, 'u' },
    { "password", 1, 0, 'w' },
    { 0, 0, 0, 0 }
};

void usage(void)
{
	fprintf(stdout, "Usage bug2issue ");
    fprintf(stdout, "[-d database] [-u username] [-h host] [-p port] [-w password] ");
    fprintf(stdout, "[-c] [-b bug_id] dir\n");
    fprintf(stdout, " -b, --bug      specify bug_id for 'comment' export mode\n");
	fprintf(stdout, " -d, --database specify database name, default is 'bugzilla'\n");
	fprintf(stdout, " -h, --host     specify database host name, default is 'localhost'\n");
	fprintf(stdout, " -c, --mode     export 'comment', default export is 'issue'\n");
	fprintf(stdout, " -p, --port     specify database port number, default is '3306'\n");
	fprintf(stdout, " -u, --username specify database login user, default is 'root'\n");
	fprintf(stdout, " -w, --password specify database login password, default is 'secret'\n");
	fprintf(stdout, " dir            specify storage folder for dumped files\n");

    exit(-1);
}

int main(int argc, char **argv)
{
    char c;
    int ret = 0;
    char cwd[MAX_PATH];

    memset(&bug2issue, 0, sizeof(struct bug2issue_cfg));
    bug2issue.sql_server = "localhost";
    bug2issue.sql_port = "3306";
    bug2issue.sql_db = "bugzilla";
    bug2issue.sql_login = "root";
    bug2issue.sql_password = "secret";
    bug2issue.issues_dir = getcwd(cwd, MAX_PATH);
    
    while (1) {
        int option_index = 0;

        c = getopt_long(argc, argv, "b:cd:h:p:u:w:", long_options, &option_index);
        if (c == EOF)
            break;

        switch (c) {
        case 'b':
            bug2issue.bug_id = optarg;
            break;
        case 'c':
            bug2issue.mode = BUG2ISSUE_EXPORT_COMMENT;
            break;
        case 'd':
            bug2issue.sql_db = optarg;
            break;
        case 'h':
            bug2issue.sql_server = optarg;
            break;
        case 'p':
            bug2issue.sql_port = optarg;
            break;
        case 'u':
            bug2issue.sql_login = optarg;
            break;
        case 'w':
            bug2issue.sql_password = optarg;
            break;
        default:
            usage();
            break;
        }
    }
    argc -= optind;
    argv += optind;
    
    if (argc < 1)
        usage();

    bug2issue.issues_dir = argv[0];

    switch (bug2issue.mode) {
    case BUG2ISSUE_EXPORT_ISSUE:
        ret = bug2issue_export_issues(&bug2issue);
        break;
    case BUG2ISSUE_EXPORT_COMMENT:
        ret = bug2issue_export_comments(&bug2issue);
        break;
    default:
        usage();
        break;
    };

    return ret;
}
