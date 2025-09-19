#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include necessary headers for HTTP server functionality.
#include "mongoose.h"

typedef struct {
    char username[256];
    char email[256];
    char ssn[11]; // SSN is 9 digits plus a possible separator
} Session;

Session session = {
    .username = "JohnDoe",
    .email = "john.doe@example.com",
    .ssn = "123-45-6789"
};

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;

        // Check if the request is for the /info route
        if (strcmp(hm->uri, "/info") == 0) {
            char response[512];
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n"
                     "Username: %s\nEmail: %s\nSSN: %s",
                     session.username, session.email, session.ssn);

            mg_send_head(nc, 200, strlen(response), "Content-Type: text/plain");
            mg_printf(nc, "%s", response);
        } else {
            // Handle other routes or return 404
            mg_send_http_error(nc, 404, "Not Found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://0.0.0.0:8000", ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on http://0.0.0.0:8000\nPress Enter to stop...");
    getchar();

    mg_mgr_free(&mgr);
    return 0;
}


Make sure you have the mongoose library installed and linked during compilation:


gcc -o myapp myapp.c -lmongoose
./myapp