#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

struct session_data {
    char username[50];
    char email[50];
    char ssn[12];
};

void handle_info(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        struct session_data *session = (struct session_data *) nc->user_data;

        if (mg_vcmp(&hm->uri, "/info") == 0 && hm->method.len == 3 && memcmp(hm->method.p, "GET", 3) == 0) {
            char response[256];
            snprintf(response, sizeof(response), "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}",
                     session->username, session->email, session->ssn);
            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nConnection: close\r\nContent-Length: %lu\r\n\r\n%s",
                      strlen(response), response);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, handle_info);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";

    struct session_data *session = (struct session_data *) malloc(sizeof(struct session_data));
    strncpy(session->username, "john_doe", sizeof(session->username) - 1);
    strncpy(session->email, "john.doe@example.com", sizeof(session->email) - 1);
    strncpy(session->ssn, "123-45-6789", sizeof(session->ssn) - 1);

    nc->user_data = session;

    printf("Starting server on port %s\n", s_http_port);

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {
        ;
    }

    mg_mgr_free(&mgr);
    free(session);
    return 0;
}