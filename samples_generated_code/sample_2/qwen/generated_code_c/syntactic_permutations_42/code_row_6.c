#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct mg_serve_http_opts s_http_server_opts;

void info_handler(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    if (ev == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/info") == 0) {
        const char *username = mg_get_http_var(&hm->body, "username", 1024);
        const char *email = mg_get_http_var(&hm->body, "email", 1024);
        const char *ssn = mg_get_http_var(&hm->body, "ssn", 1024);

        if (username && email && ssn) {
            char response[512];
            snprintf(response, sizeof(response), "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}", username, email, ssn);
            mg_send_head(nc, 200, strlen(response), "Content-Type: application/json");
            mg_printf(nc, "%s", response);
        } else {
            mg_http_send_error(nc, 400, "Bad request");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", info_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    s_http_server_opts.document_root = ".";  // Serve current directory
    printf("Starting web server on port 8000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}