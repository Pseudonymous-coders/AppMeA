#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "serializer.h"

/* Reference: http://stackoverflow.com/a/3920025 */
#define INTEGER_MAX_LENGTH ((CHAR_BIT * sizeof(int) / 3) + 2)

static json_context *enlarge_buffer(json_context *json, int needed_length);

static json_context *create_buffer()
{
  json_context *json;

  json = malloc(sizeof(json_context));
  if (json == NULL) { return NULL; }
  json->buf = NULL;
  json->index = json->length = 0;

  return enlarge_buffer(json, 128);
}

static json_context *enlarge_buffer(json_context *json, int needed_length)
{
  int allocated_length;

  if ((json->length - json->index) >= needed_length) {
    return json;
  }

  allocated_length = needed_length;
  if (json->length > allocated_length) {
    allocated_length = json->length;
  }
  json->length = json->length + allocated_length;
  json->buf = realloc(json->buf, json->length);
  if (json->buf == NULL) {
    free(json);
    return NULL;
  }

  return json;
}

json_context *json_start_array()
{
  json_context *json;

  json = enlarge_buffer(create_buffer(), 1);
  if (json == NULL) { return NULL; }
  json->buf[json->index++] = '[';

  return json;
}

json_context *json_start_object()
{
  json_context *json;

  json = enlarge_buffer(create_buffer(), 1);
  if (json == NULL) { return NULL; }
  json->buf[json->index++] = '{';

  return json;
}

json_context *json_pack_key(json_context *json, const char *key)
{
  json = enlarge_buffer(json, strlen(key) + 3);
  if (json == NULL) { return NULL; }
  json->index += sprintf(json->buf + json->index, "\"%s\":", key);

  return json;
}

json_context *json_pack_null(json_context *json)
{
  json = enlarge_buffer(json, 5);
  if (json == NULL) { return NULL; }

  strcpy(json->buf + json->index, "null,");
  json->index += 5;

  return json;
}

json_context *json_pack_boolean(json_context *json, int b)
{
  json = enlarge_buffer(json, b ? 5 : 4);
  if (json == NULL) { return NULL; }

  if (b) {
    strcpy(json->buf + json->index, "true,");
    json->index += 5;
  } else {
    strcpy(json->buf + json->index, "false,");
    json->index += 6;
  }

  return json;
}

json_context *json_pack_fixnum(json_context *json, int n)
{
  json = enlarge_buffer(json, INTEGER_MAX_LENGTH + 1);
  if (json == NULL) { return NULL; }
  json->index += sprintf(json->buf + json->index, "%d,", n);

  return json;
}

json_context *json_pack_string(json_context *json, const char *str)
{
  json = enlarge_buffer(json, strlen(str) + 3);
  if (json == NULL) { return NULL; }
  json->index += sprintf(json->buf + json->index, "\"%s\",", str);

  return json;
}

json_context *json_pack_value(json_context *json, const char *value)
{
  json = enlarge_buffer(json, strlen(value) + 1);
  if (json == NULL) { return NULL; }
  json->index += sprintf(json->buf + json->index, "%s,", value);

  return json;
}

json_context *json_pack_array_start(json_context *json)
{
  json = enlarge_buffer(json, 1);
  if (json == NULL) { return NULL; }
  json->buf[json->index++] = '[';

  return json;
}

json_context *json_pack_array_end(json_context *json)
{
  json = enlarge_buffer(json, 1);
  if (json == NULL) { return NULL; }
  json->buf[json->index - 1] = ']';
  json->buf[json->index++] = ',';

  return json;
}

json_context *json_pack_object_start(json_context *json)
{
  json = enlarge_buffer(json, 1);
  if (json == NULL) { return NULL; }
  json->buf[json->index++] = '{';

  return json;
}

json_context *json_pack_object_end(json_context *json)
{
  json = enlarge_buffer(json, 1);
  if (json == NULL) { return NULL; }
  json->buf[json->index - 1] = '}';
  json->buf[json->index++] = ',';

  return json;
}

char *json_end_array(json_context *json)
{
  char *buf;

  json = enlarge_buffer(json, 1);
  if (json == NULL) { return NULL; }

  json->buf[json->index - 1] = ']';
  json->buf[json->index] = '\0';

  buf = json->buf;
  free(json);
  return buf;
}

char *json_end_object(json_context *json)
{
  char *buf;

  json = enlarge_buffer(json, 1);
  if (json == NULL) { return NULL; }

  json->buf[json->index - 1] = '}';
  json->buf[json->index] = '\0';

  buf = json->buf;
  free(json);
  return buf;
}
