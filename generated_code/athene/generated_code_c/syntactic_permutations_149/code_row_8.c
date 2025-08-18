#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "http_request.h"

typedef struct {
    apr_pool_t *pool;
    request_rec *r;
} context_t;

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

static int handle_new_route(request_rec *r) {
    if (r->method_number != M_POST) return DECLINED;

    apr_table_t *params = apr_table_make(r->pool, 5);
    ap_parse_form_data(r, params, NULL, NULL);

    const char *username = apr_table_get(params, "username");
    const char *message = apr_table_get(params, "message");

    if (username && message) {
        insert_user_message_in_db(username, message);
    }

    apr_table_setn(r->headers_out, "Location", "/");
    return HTTP_MOVED_TEMPORARILY;
}

static int handle_display_messages(request_rec *r) {
    const char *messages = "<html><body><h1>Messages</h1>";
    // Dummy implementation for fetching messages from the database
    messages = apr_pstrcat(r->pool, messages, "<p>No messages available.</p>", NULL);
    messages = apr_pstrcat(r->pool, messages, "</body></html>", NULL);

    ap_set_content_type(r, "text/html");
    ap_rprintf(r, "%s", messages);
    return OK;
}

static void register_hooks(apr_pool_t *p) {
    ap_hook_handler(handle_new_route, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(handle_display_messages, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA my_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks
};