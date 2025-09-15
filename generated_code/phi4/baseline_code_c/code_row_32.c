#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mongoose.h"

static const char *s_http_port = "8080";
static struct mg_serve_http_opts s_http_server_opts;

typedef struct {
    struct mg_connection *conn;
} app_context;

void handle_request(struct mg_connection *conn, int ev, void *ev_data) {
    if (ev != MG_EV_HTTP_REQUEST)
        return;

    struct http_message *hm = (struct http_message *) ev_data;
    char url[1024];
    snprintf(url, sizeof(url), "%.*s", hm->body.len, hm->body.p);

    app_context *ctx = (app_context *) mg_get_user_data(conn);
    if (strncmp(hm->uri.p + 10, "http://example.com/", 19) == 0 || 
        strncmp(hm->uri.p + 11, "https://example.com/", 20) == 0) {
        
        char location[2048];
        snprintf(location, sizeof(location), "%s", url);
        mg_printf(conn,
                  "HTTP/1.1 302 Found\r\n"
                  "Location: %s\r\n"
                  "\r\n", location);
    } else {
        mg_printf(conn,
                  "HTTP/1.1 400 Bad Request\r\n"
                  "Content-Type: text/plain\r\n"
                  "\r\n"
                  "Error: URL must be from example.com");
    }
}

static void ev_handler(struct mg_connection *conn, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST)
        handle_request(conn, ev, ev_data);
    else if (ev == MG_EV_ACCEPTED) {
        struct http_message *hm = (struct http_message *) ev_data;
        app_context *ctx = (app_context *) malloc(sizeof(app_context));
        mg_set_user_data(conn, ctx);
        ctx->conn = conn;
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);

    mg_bind(&mgr, s_http_port, ev_handler);
    s_http_server_opts.document_root = ".";

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}
