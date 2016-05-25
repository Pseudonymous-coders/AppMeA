#include "client.h"
#include "distribution.h"
#include "utility.h"

m2x_response m2x_distribution_list(m2x_context *ctx)
{
  int status;
  char *out = NULL;

  status = m2x_client_get(ctx, "/distributions", &out);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_create(m2x_context *ctx, const char *data)
{
  int status;
  char *out = NULL;

  status = m2x_client_post(ctx, "/distributions", data, &out);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_view(m2x_context *ctx, const char *distribution_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s",
                                           distribution_id);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_update(m2x_context *ctx, const char *distribution_id, const char *data)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s", distribution_id);

  status = m2x_client_put(ctx, path, data, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_device_list(m2x_context *ctx, const char *distribution_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s/devices", distribution_id);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_device_add(m2x_context *ctx, const char *distribution_id, const char *data)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s/devices", distribution_id);

  status = m2x_client_post(ctx, path, data, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_delete(m2x_context *ctx, const char *distribution_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s", distribution_id);

  status = m2x_client_delete(ctx, path, NULL, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_stream_list(m2x_context *ctx, const char *distribution_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s/streams", distribution_id);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_stream_create(m2x_context *ctx, const char *distribution_id, const char *stream_name, const char *data)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s/streams/%s", distribution_id, stream_name);

  status = m2x_client_put(ctx, path, data, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_stream_view(m2x_context *ctx, const char *distribution_id, const char *stream_name)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s/streams/%s", distribution_id, stream_name);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_stream_delete(m2x_context *ctx, const char *distribution_id, const char *stream_name)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s/streams/%s", distribution_id, stream_name);

  status = m2x_client_delete(ctx, path, NULL, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_metadata(m2x_context *ctx, const char *distribution_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s/metadata",
                                           distribution_id);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_metadata_update(m2x_context *ctx,
                                              const char *distribution_id,
                                              const char *data)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s/metadata",
                                           distribution_id);

  status = m2x_client_put(ctx, path, data, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_metadata_field(m2x_context *ctx,
                                             const char *distribution_id,
                                             const char *field)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s/metadata/%s",
                                           distribution_id, field);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_distribution_metadata_field_update(m2x_context *ctx,
                                                    const char *distribution_id,
                                                    const char *field,
                                                    const char *data)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/distributions/%s/metadata/%s",
                                           distribution_id, field);

  status = m2x_client_put(ctx, path, data, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}
