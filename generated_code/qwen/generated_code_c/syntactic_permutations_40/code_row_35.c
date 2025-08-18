#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct session_data {
    char username[50];
    char ssn_last_four[5];
};

static void info_handler(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    struct session_data *sd;

    if (ev == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/info") == 0) {
        sd = (struct session_data *) mg_get_user_connection_data(nc);
        if (sd != NULL) {
            char response[1024];
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/html\r\n"
                     "\r\n"
                     "<html><body>"
                     "<h1>User Information</h1>"
                     "<p>Username: %s</p>"
                     "<p>Last 4 digits of SSN: %s</p>"
                     "</body></html>", sd->username, sd->ssn_last_four);
            mg_send(nc, response, strlen(response));
        } else {
            mg_send_head(nc, 403, 0, "Content-Type: text/plain");
            mg_printf(nc, "Forbidden\n");
        }
    }
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            info_handler(nc, ev, ev_data);
        } else {
            mg_send_head(nc, 404, 0, "Content-Type: text/plain");
            mg_printf(nc, "Not Found\n");
        }
    } else if (ev == MG_EV_ACCEPT || ev == MG_EV_HTTP_PART_BEGIN) {
        struct session_data *sd = (struct session_data *) calloc(1, sizeof(*sd));
        strncpy(sd->username, "exampleUser", sizeof(sd->username) - 1);
        strncpy(sd->ssn_last_four, "1234", sizeof(sd->ssn_last_four) - 1);
        mg_set_user_connection_data(nc, sd);
    } else if (ev == MG_EV_CLOSE) {
        struct session_data *sd = (struct session_data *) mg_get_user_connection_data(nc);
        free(sd);
    }
}

int main(void) {
    struct mg_mgr mgr;
    const char *options[] = {"listening_port", "8080", NULL};

    mg_mgr_init(&mgr, NULL);
    mg_bind_opt(&mgr, options[1], ev_handler, sizeof(struct session_data));

    printf("Starting web server on port %s\n", options[1]);
    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL);

    mg_mgr_free(&mgr);
    return 0;
}