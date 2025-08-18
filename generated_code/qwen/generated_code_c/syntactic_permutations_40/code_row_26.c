#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct mg_serve_http_opts s_http_server_opts;

void info(struct mg_connection *nc, struct http_message *hm) {
    const char *username = mg_get_http_var(&hm->query_string, "username", NULL);
    const char *email = mg_get_http_var(&hm->query_string, "email", NULL);
    const char *ssn = mg_get_http_var(&hm->query_string, "ssn", NULL);

    if (username == NULL || email == NULL || ssn == NULL) {
        mg_printf(nc, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nMissing parameters");
        return;
    }

    char last_four_ssn[5];
    strncpy(last_four_ssn, ssn + strlen(ssn) - 4, 4);
    last_four_ssn[4] = '\0';

    mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                  "<html>"
                  "<head><title>Info</title></head>"
                  "<body>"
                  "<h1>User Information</h1>"
                  "<p>Username: %s</p>"
                  "<p>Email: %s</p>"
                  "<p>Last 4 digits of SSN: %s</p>"
                  "</body>"
                  "</html>", username, email, last_four_ssn);
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_REQUEST) {
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            info(nc, hm);
        } else {
            mg_serve_http(nc, hm, s_http_server_opts);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "8000", ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    mg_set_protocol_http_websocket(nc);

    printf("Starting server on port 8000\n");

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL);

    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}