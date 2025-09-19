#include <stdio.h>
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

static void handle_info(struct mg_connection *nc, const struct mg_request_info *ri) {
    (void) ri;
    char username[] = "john_doe";
    char email[] = "john.doe@example.com";
    char ssn_last_4[] = "1234"; // Last 4 digits of SSN

    char response[512];
    snprintf(response, sizeof(response), html_response, username, email, ssn_last_4);
    mg_send(nc, response, strlen(response));
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        const struct mg_request_info *ri = (const struct mg_request_info *) ev_data;
        if (strcmp(ri->uri, "/info") == 0) {
            handle_info(nc, ri);
        } else {
            mg_send_http_error(nc, 404, "Not found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_bind(&mgr, "8080", ev_handler);
    printf("Starting server on port 8080\n");

    while (1) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}