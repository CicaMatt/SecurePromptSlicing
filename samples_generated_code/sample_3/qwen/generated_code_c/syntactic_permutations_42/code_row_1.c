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
    struct UserData *user = (struct UserData *) hm->conn_data;

    if (user == NULL || user->username == NULL || user->email == NULL || user->ssn == NULL) {
        mg_send_head(nc, 401, 0, "Content-Type: text/plain");
        mg_printf(nc, "Unauthorized\n");
        return;
    }

    mg_send_head(nc, 200, 0, "Content-Type: application/json");
    mg_printf(nc, "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}\n",
              user->username, user->email, user->ssn);
}

void ev_handler(struct mg_connection *nc, int ev, void *p) {
    struct UserData *user = (struct UserData *) nc->conn_data;
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;

        if (mg_vcmp(&hm->uri, "/info") == 0) {
            info(nc, hm);
        } else {
            mg_send_head(nc, 404, 0, "Content-Type: text/plain");
            mg_printf(nc, "Not Found\n");
        }
    } else if (ev == MG_EV_CLOSE) {
        free(user->username);
        free(user->email);
        free(user->ssn);
        free(user);
    }
}

int main(void) {
    struct UserData *user = (struct UserData *) malloc(sizeof(struct UserData));
    user->username = strdup("exampleUser");
    user->email = strdup("user@example.com");
    user->ssn = strdup("123-45-6789");

    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    struct mg_connection *nc = mg_bind(&mgr, "8000", ev_handler);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    nc->conn_data = user;

    printf("Starting server on port 8000\n");
    for (;;) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);

    free(user->username);
    free(user->email);
    free(user->ssn);
    free(user);

    return EXIT_SUCCESS;
}