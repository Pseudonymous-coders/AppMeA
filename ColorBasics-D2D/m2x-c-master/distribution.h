#ifndef M2X_DISTRIBUTION_H
#define M2X_DISTRIBUTION_H

#include "response.h"

#if defined(__cplusplus)
extern "C" {
#endif

m2x_response m2x_distribution_list(m2x_context *ctx);
m2x_response m2x_distribution_create(m2x_context *ctx, const char *data);
m2x_response m2x_distribution_view(m2x_context *ctx, const char *distribution_id);
m2x_response m2x_distribution_update(m2x_context *ctx, const char *distribution_id, const char *data);
m2x_response m2x_distribution_device_list(m2x_context *ctx, const char *distribution_id);
m2x_response m2x_distribution_device_add(m2x_context *ctx, const char *distribution_id, const char *data);
m2x_response m2x_distribution_delete(m2x_context *ctx, const char *distribution_id);

m2x_response m2x_distribution_stream_list(m2x_context *ctx, const char *distribution_id);
m2x_response m2x_distribution_stream_create(m2x_context *ctx, const char *distribution_id, const char *stream_name, const char *data);
#define m2x_distribution_stream_update m2x_distribution_stream_create
m2x_response m2x_distribution_stream_view(m2x_context *ctx, const char *distribution_id, const char *stream_name);
m2x_response m2x_distribution_stream_delete(m2x_context *ctx, const char *distribution_id, const char *stream_name);

/* Link: https://m2x.att.com/developer/documentation/v2/distribution#Read-Distribution-Metadata */
m2x_response m2x_distribution_metadata(m2x_context *ctx, const char *distribution_id);
/* Link: https://m2x.att.com/developer/documentation/v2/distribution#Update-Distribution-Metadata */
m2x_response m2x_distribution_metadata_update(m2x_context *ctx,
                                              const char *distribution_id,
                                              const char *data);
/* Link: https://m2x.att.com/developer/documentation/v2/distribution#Read-Distribution-Metadata-Field */
m2x_response m2x_distribution_metadata_field(m2x_context *ctx,
                                             const char *distribution_id,
                                             const char *field);
/* Link: https://m2x.att.com/developer/documentation/v2/distribution#Update-Distribution-Metadata-Field */
m2x_response m2x_distribution_metadata_field_update(m2x_context *ctx,
                                                    const char *distribution_id,
                                                    const char *field,
                                                    const char *data);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif  /* M2X_DISTRIBUTION_H */
