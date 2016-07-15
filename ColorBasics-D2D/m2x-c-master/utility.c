#include <ctype.h>
#include <string.h>

#include "m2x.h"
#include "utility.h"

size_t m2x_internal_encode_string(char *dst, const char *src)
{
  static const char *HEX = "0123456789ABCDEF";
  size_t len, i;

  for (i = 0, len = 0; src[i] != 0; i++) {
    if (isalnum(src[i]) ||
        (src[i] == '-') || (src[i] == '_') ||
        (src[i] == '.') || (src[i] == '~')) {
      if (dst) { dst[len] = src[i]; }
      len++;
    } else {
      if (dst) {
        dst[len] = '%';
        dst[len + 1] = HEX[src[i] / 16];
        dst[len + 2] = HEX[src[i] % 16];
      }
      len += 3;
    }
  }
  if (dst) { dst[len] = '\0'; }
  return len;
}

size_t m2x_internal_get_encoded_length(const char *src)
{
  return m2x_internal_encode_string(NULL, src);
}

char *m2x_internal_get_encoded_string(m2x_context *ctx, const char *str)
{
  size_t len;
  char *ret;

  len = m2x_internal_encode_string(NULL, str);
  ret = (char *) m2x_malloc(ctx, len + 1);
  m2x_internal_encode_string(ret, str);

  return ret;
}

int m2x_internal_encoded_sprintf(char *dst, const char *fmt, ...)
{
  va_list vl;

  va_start(vl, fmt);
  return m2x_internal_encoded_vsprintf(dst, fmt, vl);
  va_end(vl);
}

int m2x_internal_encoded_vsprintf(char *dst, const char *fmt, va_list vl)
{
  const char *str;
  int i, len;

  i = len = 0;
  while (fmt[i] != '\0') {
    if ((fmt[i] == '%') && (fmt[i + 1] == 's')) {
      str = va_arg(vl, const char *);
      if (dst) {
        len += m2x_internal_encode_string(dst + len, str);
      } else {
        len += m2x_internal_encode_string(NULL, str);
      }
      i += 2;
    } else if ((fmt[i] == '%') && (fmt[i + 1] == 'S')) {
      str = va_arg(vl, const char *);
      if (dst) { strcpy(dst + len, str); }
      len += strlen(str);
      i += 2;
    } else {
      if (dst) {
        dst[len] = fmt[i];
        dst[len + 1] = '\0';
      }
      len++;
      i++;
    }
  }
  return len;
}

char *m2x_internal_create_format_string(m2x_context *ctx, const char *fmt, ...)
{
  char *ret;
  int len;
  va_list vl;

  va_start(vl, fmt);
  len = m2x_internal_encoded_vsprintf(NULL, fmt, vl) + 1;
  va_end(vl);

  ret = (char *) m2x_malloc(ctx, len);
  va_start(vl, fmt);
  m2x_internal_encoded_vsprintf(ret, fmt, vl);
  va_end(vl);

  return ret;
}

char *m2x_internal_create_query_path(m2x_context *ctx,
                                     const char *base_path,
                                     const char *query)
{
  char *ret;
  int base_len, query_len, needs_question, len, index;

  base_len = strlen(base_path);
  query_len = query ? strlen(query) : 0;
  needs_question = (query_len > 0) ? (query[0] != '?') : 0;
  len = base_len + query_len + 1;
  if (needs_question) { len++; }

  ret = (char *) m2x_malloc(ctx, len);
  strcpy(ret, base_path);
  index = base_len;
  if (needs_question) { ret[index++] = '?'; }
  if (query_len > 0) {
    strcpy(ret + index, query);
    index += query_len;
  }
  ret[index] = '\0';

  return ret;
}
