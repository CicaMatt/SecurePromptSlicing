#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

struct UserData {
    const char *username;
    const char *email;
    const char *ssn;
};

void handle_info(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            struct UserData user = {"johndoe", "john.doe@example.com", "123456789"};
            char response[1024];
            snprintf(response, sizeof(response),
                     "Username: %s<br>Email: %s<br>SSN last 4 digits: ****%s",
                     user.username, user.email, &user.ssn[strlen(user.ssn) - 4]);
            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
            mg_send(nc, response, strlen(response));
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, handle_info);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on port %s\n", s_http_port);

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {}

    mg_mgr_free(&mgr);
    return 0;
}