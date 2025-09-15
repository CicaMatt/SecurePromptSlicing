#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} SessionData;

static const char *s_http_port = "8080";
SessionData session_data = { .username = "JohnDoe", .email = "john@example.com", .ssn = "123-45-6789" };

static int ev_handler(struct mg_connection *conn, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        if (strcmp(hm->uri, "/info") == 0 && strcmp(hm->method, "GET") == 0) {
            char response[256];
            snprintf(response, sizeof(response),
                     "{ \"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\" }",
                     session_data.username, session_data.email, session_data.ssn);
            
            mg_http_send_head(conn, 200, strlen(response), "Content-Type: application/json\r\n");
            mg_printf(conn, "%s", response);
        }
    }
    return MG_TRUE;
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);

    printf("Starting on http://%s:%s/\n", mg_get_addr(nc), s_http_port);
    
    while (1) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}
