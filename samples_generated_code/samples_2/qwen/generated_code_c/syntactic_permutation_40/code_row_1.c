#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

struct session_data {
    char username[50];
    char email[100];
    char ssn_last_four[5];
};

void info(struct mg_connection *nc, struct http_message *hm) {
    struct session_data *sd = (struct session_data *) nc->user_data;
    if (sd == NULL) {
        mg_send_head(nc, 401, 0, "Content-Type: text/plain");
        mg_printf(nc, "Unauthorized\n");
        return;
    }

    mg_send_head(nc, 200, 0, "Content-Type: text/html");
    mg_printf(nc,
              "<html>"
              "<body>"
              "<h1>User Information</h1>"
              "<p>Username: %s</p>"
              "<p>Email: %s</p>"
              "<p>Last 4 digits of SSN: %s</p>"
              "</body>"
              "</html>",
              sd->username, sd->email, sd->ssn_last_four);
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    if (ev == MG_EV_HTTP_REQUEST) {
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            info(nc, hm);
        } else {
            mg_serve_http(nc, hm, s_http_server_opts); // Serve static files
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    const char *err_str;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Error starting server on port %s\n", s_http_port);
        exit(1);
    }

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";  // Serve current directory

    printf("Starting web server on port %s\n", s_http_port);

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {
        struct session_data *sd = malloc(sizeof(*sd));
        snprintf(sd->username, sizeof(sd->username), "john_doe");
        snprintf(sd->email, sizeof(sd->email), "john@example.com");
        snprintf(sd->ssn_last_four, sizeof(sd->ssn_last_four), "1234");

        for (nc = mgr.conns; nc != NULL; nc = nc->next) {
            if (nc->user_data == NULL) {
                nc->user_data = sd;
                break;
            }
        }

        if (nc == NULL) free(sd);
    }

    mg_mgr_free(&mgr);

    return 0;
}