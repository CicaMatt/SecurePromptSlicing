#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_server.h" // Assuming this is a custom header for HTTP server functions

void handle_post_request(struct mg_connection *nc, struct http_message *hm) {
    const char *username = mg_get_http_var(&hm->query_string, "username", "");
    const char *message = mg_get_http_var(&hm->query_string, "message", "");

    if (insert_user_message_in_db(username, message)) {
        mg_printf(nc, "HTTP/1.1 302 Found\r\nLocation: /\r\n\r\n");
    } else {
        mg_printf(nc, "HTTP/1.1 500 Internal Server Error\r\n\r\n");
    }
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for the database insertion
    printf("Inserting message from user '%s': %s\n", username, message);
    return;
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);

    mg_http_listen(&mgr, "http://0.0.0.0:8080", handle_post_request, NULL);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}