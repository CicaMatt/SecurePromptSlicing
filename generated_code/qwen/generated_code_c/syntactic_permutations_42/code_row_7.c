#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct UserData {
    char *username;
    char *email;
    char *ssn;
};

static void info_handler(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        struct UserData *user = (struct UserData *) fn_data;

        if (mg_vcmp(&hm->uri, "/info") == 0 && hm->method.len == 3 && memcmp(hm->method.p, "GET", 3) == 0) {
            char response[1024];
            snprintf(response, sizeof(response), "{ \"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\" }",
                     user->username, user->email, user->ssn);
            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nConnection: close\r\n"
                        "Content-Length: %lu\r\n\r\n%s", strlen(response), response);
        }
    }
}

int main(void) {
    struct UserData user = {"john_doe", "john@example.com", "123-45-6789"};
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", info_handler, &user);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    printf("Starting server on port 8000\n");

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}