#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void info(struct mg_connection *nc, struct http_message *hm) {
    const char *username = nc->label;
    if (username == NULL || strlen(username) == 0) username = "Not Set";

    const char *email = mg_get_http_var(&hm->body, "email", NULL);
    if (email == NULL) email = "Not Set";

    const char *ssn = mg_get_http_var(&hm->body, "ssn", NULL);
    if (ssn != NULL && strlen(ssn) > 4) {
        ssn += strlen(ssn) - 4;
    } else {
        ssn = "Not Set";
    }

    const char *reply_fmt =
        "<html>"
        "<head><title>Info</title></head>"
        "<body>"
        "<h1>User Information</h1>"
        "<p>Username: %s</p>"
        "<p>Email: %s</p>"
        "<p>Last 4 of SSN: %s</p>"
        "</body>"
        "</html>";

    mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
    mg_printf_http_chunk(nc, reply_fmt, username, email, ssn);
    mg_send_http_chunk(nc, "", 0); // Indicate the end of the chunked response
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&hm->uri, "/info") == 0) {
                info(nc, hm);
            } else {
                mg_serve_http(nc, hm, s_http_server_opts); // Serve static files
            }
            break;
        default:
            break;
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener on port %s\n", s_http_port);
        return 1;
    }

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}