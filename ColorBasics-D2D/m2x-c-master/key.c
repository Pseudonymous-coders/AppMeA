#include "client.h"
#include "key.h"
#include "utility.h"

m2x_response m2x_key_list(m2x_context *ctx, const char *query)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_query_path(ctx, "/keys", query);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_key_create(m2x_context *ctx, const char *data)
{
  int status;
  char *out = NULL;

  status = m2x_client_post(ctx, "/keys", data, &out);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_key_view(m2x_context *ctx, const char *key)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/keys/%s", key);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_key_update(m2x_context *ctx, const char *key, const char *data)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/keys/%s", key);

  status = m2x_client_put(ctx, path, data, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_key_regenerate(m2x_context *ctx, const char *key)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/keys/%s/regenerate", key);

  status = m2x_client_post(ctx, path, NULL, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_key_delete(m2x_context *ctx, const char *key)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/keys/%s", key);

  status = m2x_client_delete(ctx, path, NULL, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}
