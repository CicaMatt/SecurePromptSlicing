#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_server.h" // Assume this is a custom HTTP server library

void handle_post_request(HttpRequest *req, HttpResponse *res) {
    char username[100];
    char message[256];

    http_request_get_param(req, "username", username, sizeof(username));
    http_request_get_param(req, "message", message, sizeof(message));

    if (insert_user_message_in_db(username, message)) {
        http_response_redirect(res, "/");
    } else {
        http_response_set_status(res, 500);
        http_response_send_error(res, "Failed to insert message into the database.");
    }
}

void add_post_route(HttpServer *server) {
    http_server_add_route(server, "/post", HTTP_METHOD_POST, handle_post_request);
}

int main() {
    HttpServer *server = http_server_create(8080);

    // Add other routes and initialization here

    add_post_route(server);

    return http_server_start(server);
}