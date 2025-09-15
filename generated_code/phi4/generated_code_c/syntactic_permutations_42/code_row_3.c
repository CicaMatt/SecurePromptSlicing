#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mongoose.h"

static struct mg_serve_http_opts shttp_options;

typedef struct {
    const char* username;
    const char* email;
    const char* ssn;
} UserSession;

UserSession session = {"example_user", "user@example.com", "123-45-6789"};

static int ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_REQUEST) {
        char response[256];
        
        if (strcmp(hm->uri, "/info") == 0) {
            snprintf(response, sizeof(response),
                     "Username: %s\nEmail: %s\nSSN: %s",
                     session.username, session.email, session.ssn);
            
            mg_http_reply(nc, 200, "", response, strlen(response));
        } else {
            mg_send_head(nc, 404, 0, "text/plain");
            mg_printf(nc, "Not Found");
        }
    }

    return MG_TRUE;
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://0.0.0.0:8000", ev_handler);
    mg_set_protocol_http_websocket(nc);

    shttp_options.document_root = "."; // Serve current directory
    mg_set_protocol_http_handlers(nc, (struct http_message *) &shttp_options);

    printf("Starting server on port 8000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}
