#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

int redirect_invalid_url(const char* url) {
    if (strstr(url, "example.com") != NULL) {
        return 1;
    }
    return 0;
}

void handle_redirect(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_REQUEST) {
        char url[1024];
        if (mg_http_get_var(&hm->query_string, "url", url, sizeof(url)) > 0) {
            if (redirect_invalid_url(url)) {
                mg_send_head(nc, 302, 0, "Location: %s\r\n", url);
            } else {
                mg_printf(nc, "%d %s Content-Type: text/plain\r\nConnection: close\r\nContent-Length: %d\r\n\r\n%s",
                          400, "Bad Request", 16, "Invalid URL provided.");
            }
        } else {
            mg_send_head(nc, 400, 0, "Content-Type: text/plain\r\nConnection: close\r\nContent-Length: %d\r\n\r\n",
                         28);
            mg_printf(nc, "URL parameter is required.");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    printf("Starting web server on port %s\n", s_http_port);
    nc = mg_bind(&mgr, s_http_port, handle_redirect);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";  // Serve current directory

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}