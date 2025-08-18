#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void info(struct mg_connection *nc, struct http_message *hm) {
    const char *username = mg_get_http_var(&hm->body, "username", 50);
    const char *email = mg_get_http_var(&hm->body, "email", 50);
    const char *ssn = mg_get_http_var(&hm->body, "ssn", 12);

    if (username == NULL || email == NULL || ssn == NULL) {
        mg_send_head(nc, 400, strlen("Bad Request"), "Content-Type: text/plain");
        mg_printf(nc, "%s", "Bad Request");
        return;
    }

    char response[300];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s\n", username, email, ssn);
    mg_send_head(nc, 200, strlen(response), "Content-Type: text/plain");
    mg_printf(nc, "%s", response);
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&hm->uri, "/info") == 0 && hm->method.p[0] == 'G') {
                info(nc, hm);
            } else {
                mg_serve_http(nc, hm, s_http_server_opts);
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

    printf("Starting web server on port %s\n", s_http_port);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
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