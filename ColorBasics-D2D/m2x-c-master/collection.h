#ifndef M2X_COLLECTION_H
#define M2X_COLLECTION_H

#include "response.h"

#if defined(__cplusplus)
extern "C" {
#endif

m2x_response m2x_collection_list(m2x_context *ctx, const char *query);
m2x_response m2x_collection_create(m2x_context *ctx, const char *data);
m2x_response m2x_collection_view(m2x_context *ctx, const char *collection_id);
m2x_response m2x_collection_update(m2x_context *ctx, const char *collection_id,
                                   const char *data);
m2x_response m2x_collection_delete(m2x_context *ctx, const char *collection_id);

m2x_response m2x_collection_metadata(m2x_context *ctx, const char *collection_id);
m2x_response m2x_collection_metadata_update(m2x_context *ctx,
                                            const char *collection_id,
                                            const char *data);
m2x_response m2x_collection_metadata_field(m2x_context *ctx,
                                           const char *collection_id,
                                           const char *field);
m2x_response m2x_collection_metadata_field_update(m2x_context *ctx,
                                                  const char *collection_id,
                                                  const char *field,
                                                  const char *data);

m2x_response m2x_collection_device_list(m2x_context *ctx, const char *collection_id, const char *query);


#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif  /* M2X_COLLECTION_H */
