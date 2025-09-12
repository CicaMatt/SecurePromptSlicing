#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void handle_info(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            const char *username = "JohnDoe";
            const char *email = "johndoe@example.com";
            const char *ssn_last4 = "1234";

            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\n"
                                "Content-Type: text/html; charset=utf-8\r\n"
                                "\r\n"
                                "<html><body>"
                                "<h1>User Information</h1>"
                                "<p>Username: %s</p>"
                                "<p>Email: %s</p>"
                                "<p>Last 4 digits of SSN: %s</p>"
                                "</body></html>",
                    username, email, ssn_last4);
        } else {
            mg_serve_http(nc, hm, s_http_server_opts);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    printf("Starting web server on port %s\n", s_http_port);
    nc = mg_bind(&mgr, s_http_port, handle_info);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    mg_set_protocol_http_websocket(nc);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}