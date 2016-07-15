#include "client.h"
#include "chart.h"
#include "utility.h"

m2x_response m2x_chart_list(m2x_context *ctx, const char *query)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_query_path(ctx, "/charts", query);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_chart_create(m2x_context *ctx, const char *data)
{
  int status;
  char *out = NULL;

  status = m2x_client_post(ctx, "/charts", data, &out);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_chart_view(m2x_context *ctx, const char *chart_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/charts/%s", chart_id);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_chart_update(m2x_context *ctx, const char *chart_id, const char *data)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/charts/%s", chart_id);

  status = m2x_client_put(ctx, path, data, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_chart_delete(m2x_context *ctx, const char *chart_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/charts/%s", chart_id);

  status = m2x_client_delete(ctx, path, NULL, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}
