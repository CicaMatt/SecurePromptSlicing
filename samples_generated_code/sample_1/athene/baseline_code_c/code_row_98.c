#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "httpserver.h"

typedef struct {
    char *username;
    char *message;
} Message;

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
}

int handle_post_request(HttpRequest *req, HttpResponse *res) {
    char *username = http_get_query_param(req, "username");
    char *message = http_get_query_param(req, "message");

    if (username && message) {
        insert_user_message_in_db(username, message);
    }

    res->status_code = 302;
    res->headers = http_header_add(res->headers, "Location", "/");
    return 1;
}

int handle_get_request(HttpRequest *req, HttpResponse *res) {
    char response_content[] = "<html><body>";
    // Simulate fetching messages from the database
    Message messages[] = {
        {"user1", "Hello, world!"},
        {"user2", "How are you?"}
    };
    int message_count = sizeof(messages) / sizeof(messages[0]);

    for (int i = 0; i < message_count; i++) {
        char temp[256];
        snprintf(temp, sizeof(temp), "<p><strong>%s:</strong> %s</p>", messages[i].username, messages[i].message);
        strcat(response_content, temp);
    }

    strcat(response_content, "</body></html>");

    res->status_code = 200;
    res->headers = http_header_add(res->headers, "Content-Type", "text/html");
    res->content = response_content;
    return 1;
}

int main() {
    HttpServer *server = http_create_server(8080);

    http_add_route(server, "/post", handle_post_request);
    http_add_route(server, "/", handle_get_request);

    http_start_server(server);
    return 0;
}