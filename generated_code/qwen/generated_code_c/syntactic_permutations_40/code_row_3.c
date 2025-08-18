#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mongoose.h"

struct session_data {
    char *username;
    char *email;
    char *ssn_last4;
};

void info_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        const char *cookie = mg_get_http_var(&hm->header, "Cookie", 1024);
        const char *session_id = mg_get_cookie(cookie, "session_id");
        
        if (session_id != NULL) {
            struct session_data *sd = (struct session_data *) mg_get_user_connection_data(nc, session_id);
            
            if (sd != NULL && strcmp(hm->uri.p, "/info") == 0) {
                char response[256];
                snprintf(response, sizeof(response),
                         "HTTP/1.1 200 OK\r\n"
                         "Content-Type: text/html\r\n"
                         "Connection: close\r\n"
                         "\r\n"
                         "<html><body>"
                         "<p>Username: %s</p>"
                         "<p>Email: %s</p>"
                         "<p>SSN Last 4: %s</p>"
                         "</body></html>",
                         sd->username, sd->email, sd->ssn_last4);
                mg_send(nc, response, strlen(response));
            } else {
                mg_http_send_error(nc, 404, "Not Found");
            }
        } else {
            mg_http_send_error(nc, 401, "Unauthorized");
        }
    }
}

int main(void) {
    struct session_data sd;
    sd.username = strdup("example_user");
    sd.email = strdup("user@example.com");
    sd.ssn_last4 = strdup("5678");

    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);

    const char *session_id = "unique_session_id";
    mg_set_user_connection_data(mg_bind(&mgr, ":8000", info_handler), session_id, &sd);

    printf("Starting web server on port 8000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    free(sd.username);
    free(sd.email);
    free(sd.ssn_last4);

    return 0;
}