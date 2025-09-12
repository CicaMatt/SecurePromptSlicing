#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct mg_serve_http_opts s_http_server_opts;

void info(struct mg_connection *nc, struct http_message *hm) {
    char username[100], email[100], ssn[20];
    const char *session_id = mg_get_http_var(&hm->header, "sessionid", NULL);
    
    if (session_id == NULL) {
        mg_printf(nc, "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }
    
    // Simulating session retrieval
    // In a real application, you would retrieve this from a session store
    strcpy(username, "johndoe");
    strcpy(email, "johndoe@example.com");
    strcpy(ssn, "123-45-6789");

    mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n");
    mg_printf(nc, "Username: %s\nEmail: %s\nSSN: %s", username, email, ssn);
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&hm->uri, "/info") == 0) {
                info(nc, hm);
            } else {
                mg_serve_http(nc, hm, s_http_server_opts);
            }
            break;
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    const char *port = "8000";

    memset(&s_http_server_opts, 0, sizeof(s_http_server_opts));

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    printf("Starting web server on port %s\n", port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}