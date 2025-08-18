#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_server.h" // Assuming a simple HTTP server library is used

typedef struct {
    char *username;
    char *message;
} Message;

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
}

void handle_post_request(HttpRequest *req, HttpResponse *res) {
    char *username = http_get_request_param(req, "username");
    char *message = http_get_request_param(req, "message");

    if (username && message) {
        insert_user_message_in_db(username, message);
        http_set_response_status(res, 302);
        http_set_response_header(res, "Location", "/");
    } else {
        http_set_response_status(res, 400);
        http_set_response_body(res, "Bad Request");
    }
}

void handle_get_request(HttpRequest *req, HttpResponse *res) {
    // Simulate fetching messages from the database
    Message messages[] = {
        {"user1", "Hello"},
        {"user2", "Hi there"}
    };
    size_t message_count = sizeof(messages) / sizeof(messages[0]);

    char response[4096];
    strcpy(response, "<html><body>");
    for (size_t i = 0; i < message_count; i++) {
        snprintf(response + strlen(response), sizeof(response) - strlen(response),
                 "<p><strong>%s:</strong> %s</p>", messages[i].username, messages[i].message);
    }
    strcat(response, "</body></html>");

    http_set_response_status(res, 200);
    http_set_response_header(res, "Content-Type", "text/html");
    http_set_response_body(res, response);
}

int main() {
    HttpServer *server = http_create_server(8080);

    http_add_route(server, "/post", "POST", handle_post_request);
    http_add_route(server, "/", "GET", handle_get_request);

    http_start_server(server);

    return 0;
}