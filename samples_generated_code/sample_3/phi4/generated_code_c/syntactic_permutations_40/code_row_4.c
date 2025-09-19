#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} SessionData;

static const char *s_http_port = "8000";
SessionData session_data;

void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        if (strcmp(hm->uri, "/info") == 0 && hm->method == MG_HTTP_METHOD_GET) {
            char response[512];
            snprintf(response, sizeof(response),
                     "<html><body>"
                     "<h1>User Information</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 SSN Digits: %.*s</p>"
                     "</body></html>",
                     session_data.username,
                     session_data.email,
                     4, &session_data.ssn[strlen(session_data.ssn) - 4]);
            mg_http_reply(nc, 200, "", response);
        } else {
            mg_http_reply_error(nc, MG_HTTP_STATUS_NOT_FOUND);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    const char *options[] = {"listening_ports", s_http_port, NULL};
    mg_set_option(nc, options);

    printf("Starting web server on port %s\n", s_http_port);
    
    // Simulated session data
    session_data.username = "john_doe";
    session_data.email = "johndoe@example.com";
    session_data.ssn = "123-45-6789";

    while (1) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}
