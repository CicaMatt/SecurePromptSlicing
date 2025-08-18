#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct session_data {
    char *username;
};

static void handle_get_info(struct mg_connection *nc, struct http_message *hm) {
    struct session_data *sd = (struct session_data *) mg_get_user_data(nc);
    if (sd && sd->username) {
        mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n%s", sd->username);
    } else {
        mg_send_head(nc, 401, 0, "Content-Type: text/plain\r\n");
        mg_printf(nc, "Unauthorized");
    }
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        if (mg_vcmp(&hm->uri, "/info") == 0 && hm->method.len == 3 && memcmp(hm->method.p, "GET", 3) == 0) {
            handle_get_info(nc, hm);
        }
    } else if (ev == MG_EV_ACCEPT) {
        struct session_data *sd = (struct session_data *) calloc(1, sizeof(*sd));
        sd->username = strdup("exampleUser"); // In a real application, this would be retrieved from the session
        mg_set_user_data(nc, sd);
    } else if (ev == MG_EV_CLOSE) {
        struct session_data *sd = (struct session_data *) mg_get_user_data(nc);
        free(sd->username);
        free(sd);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    const char *opts[] = {"listening_port", "8080", NULL};

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind_opt(&mgr, opts[1], ev_handler, opts);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on port %s\n", opts[1]);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}