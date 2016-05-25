#include <stdlib.h>

#include "client.h"
#include "timestamp.h"

m2x_response m2x_timestamp_json(m2x_context *ctx)
{
  int status;
  char *out = NULL;

  status = m2x_client_get(ctx, "/time", &out);
  return m2x_make_response(ctx, status, out);
}

m2x_response m2x_timestamp_seconds_raw(m2x_context *ctx)
{
  int status;
  char *out = NULL;

  status = m2x_client_get(ctx, "/time/seconds", &out);
  return m2x_make_response_no_json(ctx, status, out);
}

m2x_response m2x_timestamp_millis_raw(m2x_context *ctx)
{
  int status;
  char *out = NULL;

  status = m2x_client_get(ctx, "/time/millis", &out);
  return m2x_make_response_no_json(ctx, status, out);
}

m2x_response m2x_timestamp_iso8601_raw(m2x_context *ctx)
{
  int status;
  char *out = NULL;

  status = m2x_client_get(ctx, "/time/iso8601", &out);
  return m2x_make_response_no_json(ctx, status, out);
}

static m2x_time_t str_to_time(const char *str)
{
  m2x_time_t ret;
  int i;

  ret = 0;
  for (i = 0; str[i] != '\0'; i++) {
    switch (str[i]) {
      case '1':
        ret = ret * 10 + 1;
        break;
      case '2':
        ret = ret * 10 + 2;
        break;
      case '3':
        ret = ret * 10 + 3;
        break;
      case '4':
        ret = ret * 10 + 4;
        break;
      case '5':
        ret = ret * 10 + 5;
        break;
      case '6':
        ret = ret * 10 + 6;
        break;
      case '7':
        ret = ret * 10 + 7;
        break;
      case '8':
        ret = ret * 10 + 8;
        break;
      case '9':
        ret = ret * 10 + 9;
        break;
      default:
        /* For all the possible value left, we assume it is 0 */
        ret = ret * 10;
        break;
    }
  }
  return ret;
}

m2x_time_t m2x_timestamp_seconds_i(m2x_context *ctx)
{
  m2x_response response;
  m2x_time_t ret;

  response = m2x_timestamp_seconds_raw(ctx);

  if (m2x_is_success(&response)) {
    ret = str_to_time(response.raw);
    m2x_release_response(&response);
    return ret;
  } else {
    m2x_release_response(&response);
    return -1;
  }
}

m2x_time_t m2x_timestamp_millis_i(m2x_context *ctx)
{
  m2x_response response;
  m2x_time_t ret;

  response = m2x_timestamp_millis_raw(ctx);

  if (m2x_is_success(&response)) {
    ret = str_to_time(response.raw);
    m2x_release_response(&response);
    return ret;
  } else {
    m2x_release_response(&response);
    return -1;
  }
}

#define SIZE_ISO_8601 25
static int is_leap_year(INT16 y) {
  return ((1970 + y) > 0) &&
      !((1970 + y) % 4) &&
      (((1970 + y) % 100) || !((1970 + y) % 400));
}
static INT32 days_in_year(INT16 y) {
  return is_leap_year(y) ? 366 : 365;
}
static const UINT8 MONTH_DAYS[]={31,28,31,30,31,30,31,31,30,31,30,31};

char *m2x_timestamp_to_iso8601(m2x_context *ctx, m2x_time_t seconds, m2x_time_t millis)
{
	
  INT16 year;
  INT8 month, month_length;
  INT32 day;
  INT8 hour, minute, second;
  m2x_time_t timestamp;
  char *ret;

  ret = (char *) m2x_malloc(ctx, SIZE_ISO_8601 * sizeof(char));

  timestamp = seconds + millis / 1000;
  millis = millis % 1000;

  second = timestamp % 60;
  timestamp /= 60; /* now it is minutes */

  minute = timestamp % 60;
  timestamp /= 60; /* now it is hours */

  hour = timestamp % 24;
  timestamp /= 24; /* now it is days */

  year = 0;
  day = 0;
  while ((day += days_in_year(year)) <= timestamp) {
    year++;
  }
  day -= days_in_year(year);
  timestamp -= day; /* now it is days in this year, starting at 0 */

  day = 0;
  month_length = 0;
  for (month = 0; month < 12; month++) {
    if (month == 1) {
      /* February */
      month_length = is_leap_year(year) ? 29 : 28;
    } else {
      month_length = MONTH_DAYS[month];
    }

    if (timestamp >= month_length) {
      timestamp -= month_length;
    } else {
      break;
    }
  }
  year = 1970 + year;
  month++; /* offset by 1 */
  day = timestamp + 1;

  sprintf(ret, "%04d-%02d-%02dT%02d:%02d:%02d.%03dZ", year, month, day,
          hour, minute, second, (int) millis);
  return ret;
}
