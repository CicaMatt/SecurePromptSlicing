#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

struct SessionData {
    char username[50];
    char email[100];
    char ssn[12]; // Assuming SSN is stored as xxx-xx-xxxx
};

void info_handler(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    if (ev == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/info") == 0) {
        const char *cookie = mg_get_http_header(hm, "Cookie");
        struct SessionData *session = NULL;

        // Simple cookie parsing for demonstration purposes
        if (cookie != NULL) {
            session = (struct SessionData *) malloc(sizeof(struct SessionData));
            sscanf(cookie, "username=%49[^;]; email=%99[^;]; ssn=%11[^;]", 
                   session->username, session->email, session->ssn);
        }

        if (session != NULL) {
            char ssn_last_4[5];
            strncpy(ssn_last_4, session->ssn + 7, 4);
            ssn_last_4[4] = '\0';

            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                      "<html><body>"
                      "<h1>User Information</h1>"
                      "<p>Username: %s</p>"
                      "<p>Email: %s</p>"
                      "<p>Last 4 digits of SSN: %s</p>"
                      "</body></html>", 
                      session->username, session->email, ssn_last_4);

            free(session);
        } else {
            mg_send_head(nc, 401, 0, "Content-Type: text/html\r\nConnection: close");
            mg_printf(nc, "<html><body><h1>Unauthorized</h1></body></html>");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, info_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";  // Serve current directory

    printf("Starting web server on port %s\n", s_http_port);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return EXIT_SUCCESS;
}