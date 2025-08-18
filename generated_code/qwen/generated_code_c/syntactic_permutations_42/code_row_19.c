#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void info_handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        const char *uri = hm->uri.p;
        if (mg_vcmp(uri, "/info") == 0 && hm->method == HTTP_GET) {
            const char *username = mg_get_http_var(&hm->body, "username", NULL);
            const char *email = mg_get_http_var(&hm->body, "email", NULL);
            const char *ssn = mg_get_http_var(&hm->body, "ssn", NULL);

            char response[1024];
            snprintf(response, sizeof(response),
                     "{\"username\":\"%s\", \"email\":\"%s\", \"ssn\":\"%s\"}",
                     username ? username : "",
                     email ? email : "",
                     ssn ? ssn : "");

            mg_send_head(nc, 200, strlen(response), "Content-Type: application/json");
            mg_printf(nc, "%s", response);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    printf("Starting web server on port %s\n", s_http_port);
    nc = mg_bind(&mgr, s_http_port, info_handler);
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