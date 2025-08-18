#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void info_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        const char *path_info = hm->uri.p + 1; // Skip leading '/'
        
        if (strcmp(path_info, "info") == 0) {
            const char *username = mg_get_http_var(&hm->body, "username", NULL);
            const char *email = mg_get_http_var(&hm->body, "email", NULL);
            const char *ssn = mg_get_http_var(&hm->body, "ssn", NULL);

            if (username && email && ssn) {
                char last_four_ssn[5];
                snprintf(last_four_ssn, sizeof(last_four_ssn), "%s", ssn + strlen(ssn) - 4);
                
                mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                          "<html><body>"
                          "<h1>User Information</h1>"
                          "<p>Username: %s</p>"
                          "<p>Email: %s</p>"
                          "<p>Last 4 digits of SSN: %s</p>"
                          "</body></html>", username, email, last_four_ssn);
            } else {
                mg_send_head(nc, 400, 0, "Content-Type: text/plain");
                mg_printf(nc, "Missing parameters\n");
            }
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, info_handler);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    mg_set_protocol_http_websocket(nc);
    printf("Starting web server on port %s\n", s_http_port);

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {
    }

    mg_mgr_free(&mgr);
    return EXIT_SUCCESS;
}