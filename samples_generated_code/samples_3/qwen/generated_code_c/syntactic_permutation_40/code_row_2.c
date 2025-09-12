#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void info(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    if (ev == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/info") == 0) {
        const char *username = nc->sess_data ? (const char *)nc->sess_data : "No username";
        const char *email = "example@example.com"; // Replace with actual email retrieval
        const char *ssn_last4 = "1234"; // Replace with actual SSN last 4 digits retrieval

        mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
        mg_printf(nc, "<html><body>");
        mg_printf(nc, "<h1>User Information</h1>");
        mg_printf(nc, "<p>Username: %s</p>", username);
        mg_printf(nc, "<p>Email: %s</p>", email);
        mg_printf(nc, "<p>Last 4 digits of SSN: %s</p>", ssn_last4);
        mg_printf(nc, "</body></html>");
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, info);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    mg_set_protocol_http_websocket(nc);
    printf("Starting web server on port %s\n", s_http_port);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
    return EXIT_SUCCESS;
}