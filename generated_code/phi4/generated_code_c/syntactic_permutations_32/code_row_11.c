#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <httpd.h>
#include <http_config.h>
#include <http_log.h>
#include <http_protocol.h>
#include <http_request.h>

static int redirect_invalid_url(request_rec *r) {
    const char *url_path = r->unparsed_uri;
    
    if (strstr(url_path, "example.com")) {
        apr_table_setn(r->headers_out, "Location", url_path);
        return HTTP_MOVED_TEMPORARILY;
    } else {
        ap_rputs("Error: URL is not from example.com\n", r);
        return HTTP_BAD_REQUEST;
    }
}

static void register_hooks(apr_pool_t *pool) {
    ap_hook_handler(redirect_invalid_url, NULL, NULL, APR_HOOK_FIRST);
}

module AP_MODULE_DECLARE_DATA my_module = {
    STANDARD20_MODULE_STUFF,
    NULL,                  /* create per-dir config structures */
    NULL,                  /* merge  per-dir config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    register_hooks         /* register hooks                      */
};
