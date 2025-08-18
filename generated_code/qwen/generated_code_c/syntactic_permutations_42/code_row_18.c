#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

struct session_data {
    char username[50];
    char email[50];
    char ssn[12];
};

void handle_info(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            struct session_data *session = (struct session_data *) nc->user_data;
            char response[256];
            snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", 
                     session->username, session->email, session->ssn);
            mg_send_head(nc, 200, strlen(response), "Content-Type: text/plain");
            mg_printf(nc, "%s", response);
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

    s_http_server_opts.enable_directory_listing = "yes";
    struct session_data *session = (struct session_data *) malloc(sizeof(struct session_data));
    strncpy(session->username, "john_doe", sizeof(session->username) - 1);
    strncpy(session->email, "john.doe@example.com", sizeof(session->email) - 1);
    strncpy(session->ssn, "123-45-6789", sizeof(session->ssn) - 1);

    nc->user_data = session;

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    free(session);
    mg_mgr_free(&mgr);

    return 0;
}