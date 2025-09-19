#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mongoose.h"

typedef struct {
    char username[50];
    char email[100];
    char ssn_last4[5];
} SessionData;

static const char *s_http_port = "8080";

SessionData session_data = {"user123", "user@example.com", "6789"};

static int ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        
        if (strcmp(hm->uri, "/info") == 0 && hm->method_num == MG_MD_GET) {
            char response[256];
            
            snprintf(response, sizeof(response),
                     "<html><body>"
                     "<h1>User Information</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 Digits of SSN: %s</p>"
                     "</body></html>",
                     session_data.username, session_data.email, session_data.ssn_last4);
            
            mg_printf(nc,
                      "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html\r\n"
                      "\r\n"
                      "%s", response);
        } else {
            mg_http_send_error(nc, MG_HTTP_NOT_FOUND, NULL);
        }
    }

    return 0;
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, ev_handler);
    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}