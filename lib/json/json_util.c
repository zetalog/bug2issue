/*
 * $Id: json_util.c,v 1.4 2006/01/30 23:07:57 mclark Exp $
 *
 * Copyright (c) 2004, 2005 Metaparadigm Pte. Ltd.
 * Michael Clark <michael@metaparadigm.com>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#include "json_private.h"

struct array_list*
array_list_new(array_list_free_fn *free_fn)
{
  struct array_list *arr;

  arr = (struct array_list*)calloc(1, sizeof(struct array_list));
  if(!arr) return NULL;
  arr->size = ARRAY_LIST_DEFAULT_SIZE;
  arr->length = 0;
  arr->free_fn = free_fn;
  if(!(arr->array = (void**)calloc(sizeof(void*), arr->size))) {
    free(arr);
    return NULL;
  }
  return arr;
}

extern void
array_list_free(struct array_list *arr)
{
  int i;
  for(i = 0; i < arr->length; i++)
    if(arr->array[i]) arr->free_fn(arr->array[i]);
  free(arr->array);
  free(arr);
}

void*
array_list_get_idx(struct array_list *arr, int i)
{
  if(i >= arr->length) return NULL;
  return arr->array[i];
}

static int array_list_expand_internal(struct array_list *arr, int max)
{
  void *t;
  int new_size;

  if(max < arr->size) return 0;
  new_size = json_max(arr->size << 1, max);
  if(!(t = realloc(arr->array, new_size*sizeof(void*)))) return -1;
  arr->array = (void**)t;
  (void)memset(arr->array + arr->size, 0, (new_size-arr->size)*sizeof(void*));
  arr->size = new_size;
  return 0;
}

int
array_list_put_idx(struct array_list *arr, int idx, void *data)
{
  if(array_list_expand_internal(arr, idx)) return -1;
  if(arr->array[idx]) arr->free_fn(arr->array[idx]);
  arr->array[idx] = data;
  if(arr->length <= idx) arr->length = idx + 1;
  return 0;
}

int
array_list_add(struct array_list *arr, void *data)
{
  return array_list_put_idx(arr, arr->length, data);
}

int
array_list_length(struct array_list *arr)
{
  return arr->length;
}

struct printbuf* printbuf_new(void)
{
  struct printbuf *p;

  p = (struct printbuf*)calloc(1, sizeof(struct printbuf));
  if(!p) return NULL;
  p->size = 32;
  p->bpos = 0;
  if(!(p->buf = (char*)malloc(p->size))) {
    free(p);
    return NULL;
  }
  return p;
}


int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  char *t;
  if(p->size - p->bpos <= size) {
    int new_size = json_max(p->size * 2, p->bpos + size + 8);
#ifdef PRINTBUF_DEBUG
    mc_debug("printbuf_memappend: realloc "
	     "bpos=%d wrsize=%d old_size=%d new_size=%d\n",
	     p->bpos, size, p->size, new_size);
#endif /* PRINTBUF_DEBUG */
    if(!(t = (char*)realloc(p->buf, new_size))) return -1;
    p->size = new_size;
    p->buf = t;
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos]= '\0';
  return size;
}

#if !HAVE_VSNPRINTF && defined(WIN32)
# define vsnprintf _vsnprintf
#elif !HAVE_VSNPRINTF /* !HAVE_VSNPRINTF */
# error Need vsnprintf!
#endif /* !HAVE_VSNPRINTF && defined(WIN32) */

#if !HAVE_VASPRINTF
extern int vasprintf(char **ret, const char *fmt, va_list ap);
#endif /* !HAVE_VASPRINTF */

int sprintbuf(struct printbuf *p, const char *msg, ...)
{
  va_list ap;
  char *t;
  int size;
  char buf[128];

  /* user stack buffer first */
  va_start(ap, msg);
  size = vsnprintf(buf, 128, msg, ap);
  va_end(ap);
  /* if string is greater than stack buffer, then use dynamic string
     with vasprintf.  Note: some implementation of vsnprintf return -1
     if output is truncated whereas some return the number of bytes that
     would have been written - this code handles both cases. */
  if(size == -1 || size > 127) {
    va_start(ap, msg);
    if((size = vasprintf(&t, msg, ap)) == -1) { va_end(ap); return -1; }
    va_end(ap);
    printbuf_memappend(p, t, size);
    free(t);
    return size;
  } else {
    printbuf_memappend(p, buf, size);
    return size;
  }
}

void printbuf_reset(struct printbuf *p)
{
  p->buf[0] = '\0';
  p->bpos = 0;
}

void printbuf_free(struct printbuf *p)
{
  if(p) {
    free(p->buf);
    free(p);
  }
}

struct json_object* json_object_from_file(char *filename)
{
  struct printbuf *pb;
  struct json_object *obj;
  char buf[JSON_FILE_BUF_SIZE];
  int fd, ret;

  if((fd = open(filename, O_RDONLY)) < 0) {
    mc_error("json_object_from_file: error reading file %s: %s\n",
	     filename, strerror(errno));
    return (struct json_object*)error_ptr(-1);
  }
  if(!(pb = printbuf_new())) {
    mc_error("json_object_from_file: printbuf_new failed\n");
    return (struct json_object*)error_ptr(-1);
  }
  while((ret = read(fd, buf, JSON_FILE_BUF_SIZE)) > 0) {
    printbuf_memappend(pb, buf, ret);
  }
  close(fd);
  if(ret < 0) {
    mc_abort("json_object_from_file: error reading file %s: %s\n",
	     filename, strerror(errno));
    printbuf_free(pb);
    return (struct json_object*)error_ptr(-1);
  }
  obj = json_tokener_parse(pb->buf);
  printbuf_free(pb);
  return obj;
}

int json_object_to_file(char *filename, struct json_object *obj)
{
  const char *json_str;
  int fd, ret;
  unsigned int wpos, wsize;

  if(!obj) {
    mc_error("json_object_to_file: object is null\n");
    return -1;
  }

  if((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644)) < 0) {
    mc_error("json_object_to_file: error opening file %s: %s\n",
	     filename, strerror(errno));
    return -1;
  }

  if(!(json_str = json_object_to_json_string(obj))) { return -1; }


  wsize = (unsigned int)(strlen(json_str) & UINT_MAX); /* CAW: probably unnecessary, but the most 64bit safe */
  wpos = 0;
  while(wpos < wsize) {
    if((ret = write(fd, json_str + wpos, wsize-wpos)) < 0) {
      close(fd);
      mc_error("json_object_to_file: error writing file %s: %s\n",
	     filename, strerror(errno));
      return -1;
    }

	/* because of the above check for ret < 0, we can safely cast and add */
    wpos += (unsigned int)ret;
  }

  close(fd);
  return 0;
}
