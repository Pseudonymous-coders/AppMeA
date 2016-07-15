#ifndef M2X_UTILITY_H
#define M2X_UTILITY_H

#include <stdarg.h>

#if defined(__cplusplus)
extern "C" {
#endif

size_t m2x_internal_encode_string(char *dst, const char *src);
size_t m2x_internal_get_encoded_length(const char *src);
char *m2x_internal_get_encoded_string(m2x_context *ctx, const char *src);

int m2x_internal_encoded_sprintf(char *dst, const char *fmt, ...);
int m2x_internal_encoded_vsprintf(char *dst, const char *fmt, va_list vl);
char *m2x_internal_create_format_string(m2x_context *ctx, const char *fmt, ...);

char *m2x_internal_create_query_path(m2x_context *ctx,
                                     const char *base_path,
                                     const char *query);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif  /* M2X_UTILITY_H */
