#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *html_response = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html\r\n"
"Connection: close\r\n"
"\r\n"
"<html><body>"
"<h1>User Information</h1>"
"<p>Username: %s</p>"
"<p>Email: %s</p>"
"<p>Last 4 digits of SSN: %s</p>"
"</body></html>";

static void handle_info(struct mg_connection *nc, struct http_message *hm) {
    const char *username = "john_doe";
    const char *email = "john.doe@example.com";
    const char *ssn_last_4 = "1234";

    char response[1024];
    snprintf(response, sizeof(response), html_response, username, email, ssn_last_4);
    mg_send(nc, response, strlen(response));
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_MSG && strcmp(hm->uri.p, "/info") == 0) {
        handle_info(nc, hm);
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://0.0.0.0:8000", ev_handler, NULL);
    for (;;) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);
    return 0;
}