#ifndef M2X_JOB_H
#define M2X_JOB_H

#include "response.h"

#if defined(__cplusplus)
extern "C" {
#endif

m2x_response m2x_job_list(m2x_context *ctx, const char *query);
m2x_response m2x_job_view(m2x_context *ctx, const char *job_id);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif  /* M2X_JOB_H */
