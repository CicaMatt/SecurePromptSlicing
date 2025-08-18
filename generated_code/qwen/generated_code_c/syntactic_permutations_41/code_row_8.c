#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

struct User {
    char username[50];
    char email[100];
    char ssn_last4[5];
};

void handle_info_request(struct mg_connection *nc, struct http_message *hm) {
    struct User user = {"johndoe", "johndoe@example.com", "1234"};
    char response[500];

    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=utf-8\r\n"
             "\r\n"
             "<html>"
             "<head><title>User Info</title></head>"
             "<body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 of SSN: %s</p>"
             "</body>"
             "</html>", user.username, user.email, user.ssn_last4);

    mg_send(nc, response, strlen(response));
}

void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&hm->uri, "/info") == 0) {
                handle_info_request(nc, hm);
            } else {
                mg_serve_http(nc, hm, s_http_server_opts);  // Serve static files
            }
            break;
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    printf("Starting web server on port %s\n", s_http_port);

    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";  // Serve current directory

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}