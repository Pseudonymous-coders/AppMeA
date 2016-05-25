#include <curl/curl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "m2x.h"

m2x_context *m2x_open(const char* key)
{
  m2x_context *ctx;
  char* str;

  ctx = (m2x_context *) m2x_malloc(NULL, sizeof(m2x_context));
  memset(ctx, 0, sizeof(m2x_context));
  ctx->verbose = 0;
  ctx->expand_json = 1;
  ctx->curl = curl_easy_init();
  ctx->headers = curl_slist_append(ctx->headers, "User-Agent: M2X/3.1.1 (C libcurl)");
  ctx->headers = curl_slist_append(ctx->headers, "Content-Type: application/json");
  str = (char *) m2x_malloc(ctx, (12 + strlen(key)) * sizeof(char));
  strcpy(str, "X-M2X-KEY: ");
  strcpy(str + 11, key);
  ctx->headers = curl_slist_append(ctx->headers, str);
  m2x_free(str);
  return ctx;
}

void m2x_close(m2x_context *ctx)
{
  curl_slist_free_all(ctx->headers);
  curl_easy_cleanup(ctx->curl);
  m2x_free(ctx);
}

void m2x_set_verbose(m2x_context *ctx, int verbose)
{
  if (ctx) {
    ctx->verbose = verbose;
  }
}

void *m2x_malloc(m2x_context *ctx, size_t len)
{
  return m2x_realloc(ctx, NULL, len);
}

void *m2x_realloc(m2x_context *ctx, void *p, size_t len)
{
  void *p2;

  p2 = realloc(p, len);
  if (!p2) {
    /* Not enough memory */
    m2x_close(ctx);
    exit(ENOMEM);
  }
  return p2;
}

void m2x_free(void *p)
{
  if (p) {
    free(p);
  }
}
