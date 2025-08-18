#include <stdio.h>
#include <string.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

typedef struct {
    const char *username;
    const char *email;
    const char *ssn_last4;
} UserInfo;

// Sample user information
UserInfo user_info = {
    .username = "john_doe",
    .email = "johndoe@example.com",
    .ssn_last4 = "1234"
};

static int ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;

        // Check the request path
        if (strcmp(hm->uri, "/info") == 0 && strcmp(hm->method, "GET") == 0) {
            char response[256];
            snprintf(response, sizeof(response),
                     "<html><head><title>UserInfo</title></head>"
                     "<body><h1>User Information</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 SSN Digits: %s</p>"
                     "</body></html>",
                     user_info.username, user_info.email, user_info.ssn_last4);

            mg_send_head(nc, 200, strlen(response), "Content-Type: text/html");
            mg_printf(nc, "%s", response);
        } else {
            mg_serve_http(nc, hm, s_http_server_opts); // serve static files
        }
    }

    return MG_TRUE;
}

int main(void) {
    struct mg_mgr mgr;
    const char *addr = (const char *) "http://0.0.0.0:8000";

    mg_mgr_init(&mgr, NULL);
    mg_bind(&mgr, addr, ev_handler);

    s_http_server_opts.document_root = "."; // Serve current directory for static files
    s_http_server_opts.enable_directory_listing = "yes";

    printf("Starting web server on %s\n", addr);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}