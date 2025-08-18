#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct mg_serve_http_opts s_http_server_opts;

void info(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        const char *username = mg_get_http_var(&hm->query_string, "username", NULL);
        const char *email = mg_get_http_var(&hm->query_string, "email", NULL);
        const char *ssn = mg_get_http_var(&hm->query_string, "ssn", NULL);

        if (mg_vcmp(&hm->uri, "/info") == 0) {
            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n");
            mg_printf(nc, "Username: %s\nEmail: %s\nSSN: %s", username ? username : "", email ? email : "", ssn ? ssn : "");
        } else {
            mg_serve_http(nc, hm, s_http_server_opts);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", info);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on port 8000\n");

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {}

    mg_mgr_free(&mgr);

    return 0;
}