#include "client.h"
#include "command.h"
#include "utility.h"

m2x_response m2x_command_list(m2x_context *ctx, const char *query)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_query_path(ctx, "/commands", query);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_command_send(m2x_context *ctx, const char *data)
{
  int status;
  char *out = NULL;

  status = m2x_client_post(ctx, "/commands", data, &out);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_command_view(m2x_context *ctx, const char *command_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/commands/%s", command_id);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}
