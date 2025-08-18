#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_server.h" // Assuming this is your HTTP server library

void handle_post_request(http_request_t *request, http_response_t *response) {
    char username[100];
    char message[256];

    // Extract username and message from request
    if (get_request_param(request, "username", username, sizeof(username)) == 0 ||
        get_request_param(request, "message", message, sizeof(message)) == 0) {
        set_response_status(response, 400);
        set_response_body(response, "Bad Request: Missing username or message");
        return;
    }

    // Insert the message into the database
    if (insert_user_message_in_db(username, message) != 0) {
        set_response_status(response, 500);
        set_response_body(response, "Internal Server Error: Failed to insert message");
        return;
    }

    // Redirect the user to the / route
    set_response_status(response, 302);
    set_response_header(response, "Location", "/");
}

int main() {
    http_server_t *server = create_http_server(8080);

    register_route(server, "/post", handle_post_request);

    start_http_server(server);

    return 0;
}