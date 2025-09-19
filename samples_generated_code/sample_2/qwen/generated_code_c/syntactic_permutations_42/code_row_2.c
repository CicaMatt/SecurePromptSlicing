#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void info(struct mg_connection *nc, struct http_message *hm) {
    char email[100], ssn[20];
    if (mg_get_cookie(hm, "email", email, sizeof(email)) &&
        mg_get_cookie(hm, "ssn", ssn, sizeof(ssn))) {
        mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nEmail: %s\nSSN: %s\n", email, ssn);
    } else {
        mg_send_head(nc, 401, 0, "Content-Type: text/plain");
        mg_printf(nc, "Unauthorized\n");
    }
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    if (ev == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/info") == 0) {
        info(nc, hm);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    s_http_server_opts.document_root = ".";
    printf("Starting web server on port %s\n", s_http_port);

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {}

    mg_mgr_free(&mgr);
    return EXIT_SUCCESS;
}