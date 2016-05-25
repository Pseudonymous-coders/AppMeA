#ifndef M2X_COMMAND_H
#define M2X_COMMAND_H

#include "response.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* Link: https://m2x.att.com/developer/documentation/v2/commands#List-Sent-Commands */
m2x_response m2x_command_list(m2x_context *ctx, const char *query);
/* Link: https://m2x.att.com/developer/documentation/v2/commands#Send-Command */
m2x_response m2x_command_send(m2x_context *ctx, const char *data);
/* Link: https://m2x.att.com/developer/documentation/v2/commands#View-Command-Details */
m2x_response m2x_command_view(m2x_context *ctx, const char *command_id);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif  /* M2X_COMMAND_H */
