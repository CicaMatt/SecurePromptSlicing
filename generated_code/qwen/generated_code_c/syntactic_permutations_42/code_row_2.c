#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct session_data {
    char *username;
    char *email;
    char *ssn;
};

static void info_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        struct session_data *sd = (struct session_data *) nc->fn_data;

        if (mg_http_match_uri(hm, "/info")) {
            char response[512];
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n"
                     "Username: %s\nEmail: %s\nSSN: %s",
                     sd->username ? sd->username : "N/A",
                     sd->email ? sd->email : "N/A",
                     sd->ssn ? sd->ssn : "N/A");
            mg_http_reply(nc, 200, "", "%s", response);
        }
    }
}

int main(void) {
    struct session_data *sd = (struct session_data *) malloc(sizeof(struct session_data));
    sd->username = strdup("john_doe");
    sd->email = strdup("john.doe@example.com");
    sd->ssn = strdup("123-45-6789");

    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://localhost:8000", info_handler, (void *) sd);

    printf("Starting server at http://localhost:8000\n");
    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {
        // Polling for events
    }

    mg_mgr_free(&mgr);
    free(sd->username);
    free(sd->email);
    free(sd->ssn);
    free(sd);

    return 0;
}