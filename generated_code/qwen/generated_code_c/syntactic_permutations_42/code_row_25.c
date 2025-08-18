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

    if (userData == NULL || userData->username == NULL || userData->email == NULL || userData->ssn == NULL) {
        mg_http_send_head(nc, 404, strlen("Not Found"), "Content-Type: text/plain");
        mg_printf(nc, "User data not found\n");
        return;
    }

    char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s\n", userData->username, userData->email, userData->ssn);
    mg_http_send_head(nc, 200, strlen(response), "Content-Type: text/plain");
    mg_printf(nc, "%s", response);
}

static void event_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct UserData *userData;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&nc->uri, "/info") == 0) {
                info(nc, (struct http_message *) ev_data);
            }
            break;
        case MG_EV_ACCEPT:
            userData = malloc(sizeof(struct UserData));
            if (userData != NULL) {
                userData->username = strdup("exampleUser");
                userData->email = strdup("user@example.com");
                userData->ssn = strdup("123-45-6789");
                nc->user_data = userData;
            }
            break;
        case MG_EV_CLOSE:
            userData = (struct UserData *) nc->user_data;
            if (userData != NULL) {
                free(userData->username);
                free(userData->email);
                free(userData->ssn);
                free(userData);
            }
            break;
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", event_handler);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    printf("Starting web server on port 8000\n");

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL);

    mg_mgr_free(&mgr);
    return EXIT_SUCCESS;
}