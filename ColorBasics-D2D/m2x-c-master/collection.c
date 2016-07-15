#include "client.h"
#include "collection.h"
#include "utility.h"

m2x_response m2x_collection_list(m2x_context *ctx, const char *query)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_query_path(ctx, "/collections", query);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_collection_create(m2x_context *ctx, const char *data)
{
  int status;
  char *out = NULL;

  status = m2x_client_post(ctx, "/collections", data, &out);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_collection_view(m2x_context *ctx, const char *collection_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/collections/%s", collection_id);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_collection_update(m2x_context *ctx, const char *collection_id,
                                   const char *data)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/collections/%s", collection_id);

  status = m2x_client_put(ctx, path, data, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_collection_device_list(m2x_context *ctx,
                                        const char *collection_id,
                                        const char *query)
{
  int status;
  char *base_path, *path, *out = NULL;

  base_path = m2x_internal_create_format_string(ctx, "/collections/%s/devices",
                                                collection_id);
  path = m2x_internal_create_query_path(ctx, base_path, query);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  m2x_free(base_path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_collection_metadata(m2x_context *ctx, const char *collection_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/collections/%s/metadata",
                                           collection_id);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_collection_metadata_update(m2x_context *ctx,
                                            const char *collection_id,
                                            const char *data)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/collections/%s/metadata",
                                           collection_id);

  status = m2x_client_put(ctx, path, data, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_collection_metadata_field(m2x_context *ctx,
                                           const char *collection_id,
                                           const char *field)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/collections/%s/metadata/%s",
                                           collection_id, field);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_collection_metadata_field_update(m2x_context *ctx,
                                                  const char *collection_id,
                                                  const char *field,
                                                  const char *data)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/collections/%s/metadata/%s",
                                           collection_id, field);

  status = m2x_client_put(ctx, path, data, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_collection_delete(m2x_context *ctx, const char *collection_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/collections/%s", collection_id);

  status = m2x_client_delete(ctx, path, NULL, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}
