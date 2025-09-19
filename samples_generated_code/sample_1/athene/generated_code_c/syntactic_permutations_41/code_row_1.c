#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *get_user_info() {
    static char user_info[256];
    snprintf(user_info, sizeof(user_info), 
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: john_doe</p>"
             "<p>Email: john.doe@example.com</p>"
             "<p>Social Security Number: 123-45-6789</p>"
             "</body></html>");
    return user_info;
}

static void handle_request(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        if (strcmp(hm->uri.p, "/info") == 0) {
            const char *user_info = get_user_info();
            mg_printf(nc,
                      "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html\r\n"
                      "Content-Length: %d\r\n\r\n%s",
                      (int) strlen(user_info), user_info);
        } else {
            mg_send_head(nc, 404, -1, "Content-Type: text/plain");
            mg_printf_data(nc, "Not found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://0.0.0.0:8000", handle_request, NULL);
    printf("Starting web server on port 8000...\n");
    for (;;) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);
    return 0;
}