#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct UserData {
    char *username;
    char *email;
    char *ssn;
};

void info(struct mg_connection *nc, struct http_message *hm) {
    struct mg_session session = mg_get_session(nc);
    struct UserData *userData = (struct UserData *)mg_session_get_var(&session, "user");

    if (userData != NULL) {
        char response[1024];
        snprintf(response, sizeof(response), "{ \"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\" }",
                 userData->username, userData->email, userData->ssn);
        mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nConnection: close\r\nContent-Length: %lu\r\n\r\n%s", strlen(response), response);
    } else {
        mg_send_head(nc, 404, 0, "Content-Type: text/plain");
        mg_printf(nc, "User data not found.");
    }
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&hm->uri, "/info") == 0) {
                info(nc, hm);
            } else {
                mg_send_head(nc, 404, 0, "Content-Type: text/plain");
                mg_printf(nc, "Not Found\n");
            }
            break;
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    const char *opts = "s_http_port=8000";

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, opts, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    printf("Starting web server on port %s\n", opts);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}