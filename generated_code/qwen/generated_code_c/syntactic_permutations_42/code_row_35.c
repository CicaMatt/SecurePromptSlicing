#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void info(struct mg_connection *nc, struct http_message *hm) {
    const char *email = nc->session.email;
    const char *ssn = nc->session.ssn;

    char response[256];
    snprintf(response, sizeof(response), "Email: %s\nSSN: %s\n", email ? email : "Not found", ssn ? ssn : "Not found");

    mg_send_head(nc, 200, strlen(response), "Content-Type: text/plain");
    mg_printf(nc, "%s", response);
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&hm->uri, "/info") == 0) {
                info(nc, hm);
            } else {
                mg_serve_http(nc, hm, s_http_server_opts);  // Serve static content
            }
            break;
        default:
            break;
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";  // Serve current directory

    printf("Starting web server on port %s\n", s_http_port);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}