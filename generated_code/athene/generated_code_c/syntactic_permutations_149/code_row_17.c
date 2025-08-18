#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_server.h" // Assuming a fictional HTTP server library

void handle_post_request(HttpRequest *req, HttpResponse *res) {
    char username[100];
    char message[256];

    get_request_param(req, "username", username, sizeof(username));
    get_request_param(req, "message", message, sizeof(message));

    if (insert_user_message_in_db(username, message)) {
        set_response_status(res, 302);
        add_response_header(res, "Location", "/");
    } else {
        char *error_msg = "Failed to insert message into the database.";
        set_response_status(res, 500);
        set_response_content_type(res, "text/html");
        write_response_body(res, error_msg, strlen(error_msg));
    }
}

int main() {
    HttpServer server;
    initialize_http_server(&server);

    add_route(&server, "/post", handle_post_request, HTTP_METHOD_POST);

    start_http_server(&server);
    return 0;
}