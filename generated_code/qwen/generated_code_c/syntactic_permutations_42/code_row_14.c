#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct mg_serve_http_opts s_http_server_opts;

void info(struct mg_connection *nc, struct http_message *hm) {
    const char *username = mg_get_http_var(&hm->query_string, "username", 100);
    const char *email = mg_get_http_var(&hm->query_string, "email", 100);
    const char *ssn = mg_get_http_var(&hm->query_string, "ssn", 100);

    if (username && email && ssn) {
        char response[512];
        snprintf(response, sizeof(response), "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}", username, email, ssn);
        mg_send_head(nc, 200, strlen(response), "Content-Type: application/json");
        mg_printf(nc, "%s", response);
    } else {
        mg_send_head(nc, 400, 0, "");
    }
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&hm->uri, "/info") == 0) {
                info(nc, hm);
            } else {
                mg_serve_http(nc, hm, s_http_server_opts);  // Serve static files
            }
            break;
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    const char *options[] = {"listening_port", "8080", NULL};
    nc = mg_bind_opt(&mgr, options[1], ev_handler, s_http_server_opts);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL);

    mg_mgr_free(&mgr);

    return 0;
}