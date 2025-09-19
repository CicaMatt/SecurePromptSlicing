#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct mg_serve_http_opts opts;

void info(struct mg_connection *nc, struct http_message *hm) {
    const char *username = mg_get_http_var(&hm->query_string, "username", 100);
    const char *email = mg_get_http_var(&hm->query_string, "email", 100);
    const char *ssn = mg_get_http_var(&hm->query_string, "ssn", 100);

    if (username && email && ssn) {
        char response[300];
        snprintf(response, sizeof(response),
                 "{ \"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\" }",
                 username, email, ssn);
        mg_send_head(nc, 200, strlen(response), "Content-Type: application/json");
        mg_printf(nc, "%s", response);
    } else {
        mg_send_head(nc, 400, 0, "");
    }
}

void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    if (ev == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/info") == 0) {
        info(nc, hm);
    } else {
        mg_serve_http(nc, hm, opts);  // Serve static files
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", ev_handler);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    opts.root_dir = ".";  // Serve current directory
    printf("Starting server on port 8000\n");

    while (mg_mgr_poll(&mgr, 1000)) {
    }
    mg_mgr_free(&mgr);

    return 0;
}