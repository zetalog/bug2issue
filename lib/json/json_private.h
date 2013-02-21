#ifndef _json_private_h_
#define _json_private_h_

#include "json.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef WIN32
# include <windows.h>
# include <io.h>
#endif /* defined(WIN32) */

#ifdef WIN32
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_FCNTL_H 1
#define HAVE_STDARG_H 1
#define STDC_HEADERS 1
#endif

#if STDC_HEADERS
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <limits.h>
# include <errno.h>
#endif /* STDC_HEADERS */

#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */

#if HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif /* HAVE_SYS_STAT_H */

#if HAVE_FCNTL_H
#include <fcntl.h>
#endif /* HAVE_FCNTL_H */

#if HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */

#if HAVE_STDARG_H
# include <stdarg.h>
#endif /* HAVE_STDARG_H */

#if HAVE_SYSLOG_H
# include <syslog.h>
#endif /* HAVE_SYSLOG_H */

#if HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif /* HAVE_SYS_PARAM_H */

#if defined HAVE_STRINGS_H && !defined _STRING_H && !defined __USE_BSD
# include <strings.h>
#endif /* HAVE_STRINGS_H */

#if !HAVE_STRNDUP
  char* strndup(const char* str, size_t n);
#endif /* !HAVE_STRNDUP */

#if !HAVE_STRNCASECMP && defined(_MSC_VER)
  /* MSC has the version as _strnicmp */
# define strncasecmp _strnicmp
#elif !HAVE_STRNCASECMP
# error You do not have strncasecmp on your system.
#endif /* HAVE_STRNCASECMP */

#if !HAVE_OPEN && defined(WIN32)
# define open _open
#endif

#undef PRINTBUF_DEBUG

struct printbuf {
  char *buf;
  int bpos;
  int size;
};

extern struct printbuf*
printbuf_new(void);

/* As an optimization, printbuf_memappend is defined as a macro that
 * handles copying data if the buffer is large enough; otherwise it
 * invokes printbuf_memappend_real() which performs the heavy lifting
 * of realloc()ing the buffer and copying data.
 */
extern int
printbuf_memappend(struct printbuf *p, const char *buf, int size);

#define printbuf_memappend_fast(p, bufptr, bufsize)          \
do {                                                         \
  if ((p->size - p->bpos) > bufsize) {                       \
    memcpy(p->buf + p->bpos, (bufptr), bufsize);             \
    p->bpos += bufsize;                                      \
    p->buf[p->bpos]= '\0';                                   \
  } else {  printbuf_memappend(p, (bufptr), bufsize); }      \
} while (0)

extern int
sprintbuf(struct printbuf *p, const char *msg, ...);

extern void
printbuf_reset(struct printbuf *p);

extern void
printbuf_free(struct printbuf *p);

#define ARRAY_LIST_DEFAULT_SIZE 32

typedef void (array_list_free_fn) (void *data);

struct array_list
{
  void **array;
  int length;
  int size;
  array_list_free_fn *free_fn;
};

extern struct array_list*
array_list_new(array_list_free_fn *free_fn);

extern void
array_list_free(struct array_list *al);

extern void*
array_list_get_idx(struct array_list *al, int i);

extern int
array_list_put_idx(struct array_list *al, int i, void *data);

extern int
array_list_add(struct array_list *al, void *data);

extern int
array_list_length(struct array_list *al);

typedef void (json_object_delete_fn)(struct json_object *o);
typedef int (json_object_to_json_string_fn)(struct json_object *o,
					    struct printbuf *pb);

struct json_object
{
  enum json_type o_type;
  json_object_delete_fn *_delete;
  json_object_to_json_string_fn *_to_json_string;
  int _ref_count;
  struct printbuf *_pb;
  union data {
    boolean c_boolean;
    double c_double;
    int c_int;
    struct lh_table *c_object;
    struct array_list *c_array;
    char *c_string;
  } o;
};

/* CAW: added for ANSI C iteration correctness */
struct json_object_iter
{
	char *key;
	struct json_object *val;
	struct lh_entry *entry;
};

#endif
