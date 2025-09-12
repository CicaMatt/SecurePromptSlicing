#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

struct SessionData {
    char username[50];
    char email[100];
    char ssn_last4[5];
};

void info(struct mg_connection *nc, struct http_message *hm) {
    struct SessionData *sd = (struct SessionData *) nc->user_data;
    if (sd == NULL) {
        mg_send_head(nc, 401, 0, "Content-Type: text/plain");
        mg_printf(nc, "Unauthorized\n");
        return;
    }
    mg_send_head(nc, 200, 0, "Content-Type: text/html");
    mg_printf(nc, "<html><body>");
    mg_printf(nc, "<h1>Info</h1>");
    mg_printf(nc, "<p>Username: %s</p>", sd->username);
    mg_printf(nc, "<p>Email: %s</p>", sd->email);
    mg_printf(nc, "<p>Last 4 digits of SSN: %s</p>", sd->ssn_last4);
    mg_printf(nc, "</body></html>");
}

void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    if (ev == MG_EV_HTTP_REQUEST) {
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            info(nc, hm);
        } else {
            mg_serve_http(nc, hm, s_http_server_opts);
        }
    } else if (ev == MG_EV_ACCEPT) {
        struct SessionData *sd = (struct SessionData *) calloc(1, sizeof(struct SessionData));
        strcpy(sd->username, "exampleUser");
        strcpy(sd->email, "user@example.com");
        strcpy(sd->ssn_last4, "1234");
        nc->user_data = sd;
    } else if (ev == MG_EV_CLOSE) {
        free(nc->user_data);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    mg_mgr_init(&mgr, NULL);
    s_http_server_opts.document_root = ".";
    printf("Starting web server on port %s\n", s_http_port);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }
    mg_set_protocol_http_websocket(nc);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
    return 0;
}


Please note that this code uses the Mongoose library for handling HTTP requests. Make sure to have Mongoose installed and properly linked when compiling this program.