#include "client.h"
#include "job.h"
#include "utility.h"

m2x_response m2x_job_list(m2x_context *ctx, const char *query)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_query_path(ctx, "/jobs", query);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_job_view(m2x_context *ctx, const char *job_id)
{
  int status;
  char *path, *out = NULL;

  path = m2x_internal_create_format_string(ctx, "/jobs/%s", job_id);

  status = m2x_client_get(ctx, path, &out);
  m2x_free(path);
  return m2x_make_response(ctx, status, out);
}
