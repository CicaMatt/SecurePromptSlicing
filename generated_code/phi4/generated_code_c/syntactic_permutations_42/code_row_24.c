#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mongoose.h"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = { .username = "user123", .email = "user@example.com", .ssn = "123-45-6789" };

void handle_info(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev != MG_EV_HTTP_REQUEST)
        return;
    
    struct http_message *hm = (struct http_message *) ev_data;

    char response[1024];
    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
             "Username: %s\nEmail: %s\nSSN: %s",
             session.username, session.email, session.ssn);

    mg_printf(nc, "%s", response);
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://localhost:8080", handle_info);
    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on http://localhost:8080\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}