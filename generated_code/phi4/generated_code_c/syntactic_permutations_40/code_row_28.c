#include <stdio.h>
#include <stdlib.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

typedef struct {
    char username[50];
    char email[100];
    char ssn[15]; // SSN with last 4 digits
} SessionData;

SessionData session_data = {"user123", "user@example.com", "123-45-6789"};

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        
        if (mg_vcmp(&hm->uri, "/info") == 0 && hm->method_number == MG_MD_GET) {
            char response[512];
            
            snprintf(response, sizeof(response),
                     "<html><body>"
                     "<h1>User Info</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 SSN digits: %s</p>"
                     "</body></html>",
                     session_data.username,
                     session_data.email,
                     &session_data.ssn[7]);
            
            mg_serve_http(nc, (struct http_message *) p, s_http_server_opts, response);
        } else {
            mg_serve_http(nc, hm, s_http_server_opts, NULL);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = "."; // Serve current directory

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}


Compile and run the code with Mongoose library:

gcc -o webapp main.c -lmongoose
./webapp


Ensure you have `mongoose.h` and `libmongoose.a` or link against your system's mongoose installation.