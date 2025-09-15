#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mongoose.h"

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4_digits;
} UserSession;

UserSession user_session = { .username = "JohnDoe", .email = "john.doe@example.com", .ssn_last_4_digits = "1234" };

static const char *s_http_port = "8080";

static int ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            char response[1024];
            snprintf(response, sizeof(response),
                     "<html><body>"
                     "Username: %s<br>"
                     "Email: %s<br>"
                     "Last 4 digits of SSN: %s"
                     "</body></html>",
                     user_session.username,
                     user_session.email,
                     user_session.ssn_last_4_digits);

            mg_send_head(nc, 200, strlen(response), "Content-Type: text/html");
            mg_printf(nc, "%s", response);
        } else {
            mg_serve_http(nc, (struct http_message *) ev_data, s_default_http_server_opts);
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
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_destroy(&mgr);
    return 0;
}
