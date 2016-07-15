#ifndef M2X_TIMESTAMP_H
#define M2X_TIMESTAMP_H

#include <time.h>

#include "response.h"

#if defined(__cplusplus)
extern "C" {
#endif

m2x_response m2x_timestamp_json(m2x_context *ctx);

/*
 * For the following API functions, no JSON object will be generated
 * since the response is in RAW text.
 */
m2x_response m2x_timestamp_seconds_raw(m2x_context *ctx);
m2x_response m2x_timestamp_millis_raw(m2x_context *ctx);
m2x_response m2x_timestamp_iso8601_raw(m2x_context *ctx);

#ifdef M2X_ENABLE_LONG_LONG
typedef long long m2x_time_t;
#else  /* M2X_ENABLE_LONG_LONG */
typedef long m2x_time_t;
#endif  /* M2X_ENABLE_LONG_LONG */

/*
 * The following API functions can be used to fetch numeric timestamp
 * directly from M2X server.
 *
 * Since we are using timestamp directly returned from M2X, we cannot
 * simply cast it to time_t, since C89 standard says nothing about the
 * internal structure of time_t. The best we can do, is to break the
 * timestamp returned from M2X into struct tm.
 *
 * In case of error, those 2 functions will always return -1, this is
 * for simplicity reasons, for details of the error log, please use the
 * corresponding API function that returns a m2x_response.
 */
m2x_time_t m2x_timestamp_seconds_i(m2x_context *ctx);
m2x_time_t m2x_timestamp_millis_i(m2x_context *ctx);

/*
 * Converts an M2X timestamp to ISO8601.
 *
 * Notice this function takes 2 parts: seconds and millis, the generated
 * time will be the sum of both parts. If you only have one part, simply
 * pass in 0 as the other part. We use 2 parts to make this function more
 * flexible.
 *
 * One example of using this API, is that +seconds+ can be provided via
 * a call to M2X server, while +millis+ can be provided via an internal
 * clock keeping the time since last time API call. The result of this
 * function will still be an ISO8601 timestamp documenting current time,
 * extra time API call is also saved in this case.
 */
char *m2x_timestamp_to_iso8601(m2x_context *ctx, m2x_time_t seconds, m2x_time_t millis);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif  /* M2X_TIMESTAMP_H */
