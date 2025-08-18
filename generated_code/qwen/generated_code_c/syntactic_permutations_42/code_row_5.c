#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct session_data {
    char *username;
    char *email;
    char *ssn;
};

static void info_handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        struct session_data *sd = (struct session_data *) nc->user_data;

        if (mg_vcmp(&hm->uri, "/info") != 0)
            return;

        char response[256];
        snprintf(response, sizeof(response),
                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n"
                 "\r\nUsername: %s\nEmail: %s\nSSN: %s",
                 sd->username ? sd->username : "",
                 sd->email ? sd->email : "",
                 sd->ssn ? sd->ssn : "");

        mg_send(nc, response, strlen(response));
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

    mg_set_protocol_http_websocket(nc);

    struct session_data *sd = (struct session_data *) malloc(sizeof(struct session_data));
    sd->username = strdup("john_doe");
    sd->email = strdup("john.doe@example.com");
    sd->ssn = strdup("123-45-6789");

    nc->user_data = sd;

    printf("Starting server on port 8000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    free(sd->username);
    free(sd->email);
    free(sd->ssn);
    free(sd);

    return 0;
}