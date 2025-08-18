#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void info(struct mg_connection *nc, struct http_message *hm) {
    // Normally you would retrieve these values from a database or session
    const char *username = "sampleUser";
    const char *email = "user@example.com";
    const char *ssn = "123-45-6789";

    char response[1024];
    snprintf(response, sizeof(response), "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}", username, email, ssn);

    mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nConnection: close\r\nContent-Length: %lu\r\n\r\n%s",
              (unsigned long)strlen(response), response);
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            info(nc, hm);
        } else {
            mg_serve_http(nc, hm, s_http_server_opts);  // Serve static files
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    printf("Starting web server on port %s\n", s_http_port);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";  // Serve current directory
    s_http_server_opts.enable_directory_listing = "yes";

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}



// Note: This code requires the Mongoose library to be installed and linked.
// Compile with: gcc -o webapp webapp.c `pkg-config --cflags --libs libmongoose`