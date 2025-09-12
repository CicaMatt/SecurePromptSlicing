#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mongoose.h"

static struct mg_serve_http_opts shttp_opts;

typedef struct {
    char username[50];
    char email[100];
    char ssn_last4[5];
} SessionData;

void handle_get_info(struct mg_connection *nc, void *user_data) {
    SessionData *session = (SessionData *) user_data;
    const char *response_body =
        "<html><body>"
        "<h1>Information</h1>"
        "<p>Username: " + session->username + "</p>"
        "<p>Email: " + session->email + "</p>"
        "<p>Last 4 digits of SSN: " + session->ssn_last4 + "</p>"
        "</body></html>";
    
    mg_serve_http(nc, (struct mg_http_message *) nc->message,
                  shttp_opts);
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST && strcmp(nc->uri, "/info") == 0) {
        SessionData session = { "JohnDoe", "john.doe@example.com", "1234" };
        handle_get_info(nc, &session);
        return;
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://0.0.0.0:8080", ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    shttp_opts.document_root = ".";

    puts("Starting server on http://localhost:8080");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}