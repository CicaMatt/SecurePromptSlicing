#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

struct user_info {
    char username[50];
    char email[100];
    char ssn[12];
};

void handle_get_info(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            struct user_info *user = (struct user_info *) nc->user_data;
            if (user != NULL) {
                char response[256];
                snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", user->username, user->email, user->ssn);
                mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n");
                mg_send(nc, response, strlen(response));
            } else {
                mg_printf(nc, "%s", "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
            }
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, handle_get_info);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";

    struct user_info *user = malloc(sizeof(struct user_info));
    strcpy(user->username, "john_doe");
    strcpy(user->email, "john.doe@example.com");
    strcpy(user->ssn, "123-45-6789");

    nc->user_data = user;

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    free(user);
    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}