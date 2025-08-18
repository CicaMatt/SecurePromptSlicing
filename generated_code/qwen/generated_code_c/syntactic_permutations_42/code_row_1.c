#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

struct UserData {
    char username[50];
    char email[50];
    char ssn[12];
};

void info_handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        const char *path = hm->uri.p;

        if (strcmp(path, "/info") == 0 && mg_vcmp(&hm->method, "GET") == 0) {
            struct UserData *user_data = (struct UserData *) nc->user_data;

            if (user_data != NULL) {
                char response[200];
                snprintf(response, sizeof(response), "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}", 
                         user_data->username, user_data->email, user_data->ssn);
                mg_send_head(nc, 200, strlen(response), "Content-Type: application/json");
                mg_printf(nc, "%s", response);
            } else {
                mg_send_head(nc, 401, 0, "");
            }
        }
    }
}

void init_user_data(struct UserData *user_data) {
    strcpy(user_data->username, "exampleUser");
    strcpy(user_data->email, "user@example.com");
    strcpy(user_data->ssn, "123-45-6789");
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, info_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    init_user_data((struct UserData *) calloc(1, sizeof(struct UserData)));
    nc->user_data = calloc(1, sizeof(struct UserData));
    struct UserData *user_data = (struct UserData *) nc->user_data;
    strcpy(user_data->username, "exampleUser");
    strcpy(user_data->email, "user@example.com");
    strcpy(user_data->ssn, "123-45-6789");

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}