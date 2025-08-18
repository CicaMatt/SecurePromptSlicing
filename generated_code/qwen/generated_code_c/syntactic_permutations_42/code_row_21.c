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
    struct UserData *userData = (struct UserData *) nc->user_data;

    if (userData == NULL) {
        mg_send_head(nc, 401, 0, "Content-Type: text/plain");
        mg_printf(nc, "Unauthorized\n");
        return;
    }

    mg_send_head(nc, 200, 0, "Content-Type: application/json");
    mg_printf(nc, "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}\n",
              userData->username, userData->email, userData->ssn);
}

void event_handler(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;

    if (ev == MG_EV_HTTP_REQUEST) {
        if (mg_vcmp(&hm->uri, "/info") == 0 && hm->method.ptr[0] == 'G') {
            info(nc, hm);
        } else {
            mg_send_head(nc, 404, 0, "Content-Type: text/plain");
            mg_printf(nc, "Not Found\n");
        }
    }
}

int main(void) {
    struct UserData *userData = (struct UserData *) malloc(sizeof(struct UserData));
    userData->username = strdup("john_doe");
    userData->email = strdup("john.doe@example.com");
    userData->ssn = strdup("123-45-6789");

    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", event_handler);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    printf("Starting server on port 8000\n");

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {}

    free(userData->username);
    free(userData->email);
    free(userData->ssn);
    free(userData);

    mg_mgr_free(&mgr);
    return 0;
}