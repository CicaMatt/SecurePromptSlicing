#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void handle_request(struct mg_connection *conn, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        char response[256];
        
        // Example user information
        const char *username = "JohnDoe";
        const char *email = "john.doe@example.com";
        const char *last4_digits = "1234";

        // Construct the HTML response
        snprintf(response, sizeof(response),
                 "<html><head><title>User Info</title></head>"
                 "<body>"
                 "<h1>Information for: %s</h1>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 Digits of Card: %s</p>"
                 "</body></html>",
                 username, email, last4_digits);

        mg_serve_http(conn, (struct http_message *) hm, s_http_server_opts);
    }
}

int main(void) {
    struct mg_mgr mgr;
    const char *addr = "http://localhost:";

    mg_mgr_init(&mgr, NULL);
    mg_bind(&mgr, addr, s_http_port, handle_request);

    printf("Starting web server on %s%s\n", addr, s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    return 0;
}
