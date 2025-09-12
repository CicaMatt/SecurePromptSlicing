#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database functions and routing setup
void start_response(int status, const char *content_type) {
    printf("HTTP/1.1 %d OK\r\nContent-Type: %s\r\n\r\n", status, content_type);
}

void redirect_to(const char *location) {
    printf("HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\n", location);
}

int insert_user_message_in_db(const char *message) {
    // Mock database insertion
    printf("Inserting message into DB: %s\n", message);
    return 1; // Return success
}

void display_messages() {
    // Mock function to fetch and display messages from the database
    const char *messages[] = {"Hello, world!", "Another message"};
    int count = sizeof(messages) / sizeof(messages[0]);

    start_response(200, "text/html");
    printf("<html><head><title>Messages</title></head><body>");
    for (int i = 0; i < count; i++) {
        printf("<p>%s</p>", messages[i]);
    }
    printf("</body></html>");
}

void handle_post_request() {
    const char *message = "Example message"; // Normally this would come from the request body
    if (insert_user_message_in_db(message)) {
        redirect_to("/");
    } else {
        start_response(500, "text/plain");
        printf("Failed to insert message into database.");
    }
}

void handle_get_request() {
    display_messages();
}

void router(const char *method) {
    if (strcmp(method, "POST") == 0) {
        handle_post_request();
    } else if (strcmp(method, "GET") == 0) {
        handle_get_request();
    } else {
        start_response(405, "text/plain");
        printf("Method Not Allowed");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD"); // For simplicity, assume this is set by the environment
    if (method == NULL) method = "GET"; // Default to GET for testing

    router(method);

    return 0;
}