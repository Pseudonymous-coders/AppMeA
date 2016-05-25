#ifndef M2X_RESPONSE_H
#define M2X_RESPONSE_H

#include "m2x.h"
#include "third_party/parson/parson.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct m2x_response {
  int status;
  /* Optional location from response header */
  char *location;
  /* Raw response from server */
  char *raw;
  /* Parsed JSON representation */
  JSON_Value *json;
} m2x_response;

m2x_response m2x_make_response(m2x_context *ctx, int status, char *raw);
m2x_response m2x_make_response_with_location(m2x_context *ctx, int status,
                                             char *raw, char *location);
m2x_response m2x_make_response_no_json(m2x_context *ctx, int status, char *raw);
int m2x_is_success(const m2x_response *response);
int m2x_is_client_error(const m2x_response *response);
int m2x_is_server_error(const m2x_response *response);
int m2x_is_error(const m2x_response *response);
void m2x_release_response(m2x_response *response);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif  /* M2X_H */
