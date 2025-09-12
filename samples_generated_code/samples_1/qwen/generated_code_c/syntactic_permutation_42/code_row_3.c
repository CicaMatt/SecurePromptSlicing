#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

#define MAX_SESSION_DATA_SIZE 256

struct mg_serve_http_opts opts;

void handle_info(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            const char *session_id = mg_get_http_var(&hm->header, "cookie", 7);
            struct mg_connection *snc = mg_find_http_stream(nc->mgr, session_id);
            
            if (snc != NULL) {
                char username[MAX_SESSION_DATA_SIZE];
                char email[MAX_SESSION_DATA_SIZE];
                char ssn[MAX_SESSION_DATA_SIZE];

                mg_get_var(snc->label, MAX_SESSION_DATA_SIZE, "username", username, sizeof(username));
                mg_get_var(snc->label, MAX_SESSION_DATA_SIZE, "email", email, sizeof(email));
                mg_get_var(snc->label, MAX_SESSION_DATA_SIZE, "ssn", ssn, sizeof(ssn));

                char response[512];
                snprintf(response, sizeof(response), "{\"username\":\"%s\", \"email\":\"%s\", \"ssn\":\"%s\"}", username, email, ssn);
                
                mg_printf(nc, "HTTP/1.1 200 OK\r\n"
                              "Content-Type: application/json\r\n"
                              "Connection: close\r\n"
                              "Content-Length: %zu\r\n"
                              "\r\n%s", strlen(response), response);
            } else {
                mg_send_head(nc, 401, 0, "Content-Type: text/plain");
                mg_printf(nc, "Unauthorized");
            }
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", handle_info);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    opts.root_dir = ".";
    opts.extra_headers = "Server: Mongoose";

    printf("Starting web server on port 8000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}