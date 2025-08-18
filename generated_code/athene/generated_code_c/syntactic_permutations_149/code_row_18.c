#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock HTTP request structure
typedef struct {
    char *username;
    char *message;
} HttpRequest;

// Mock database function
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
}

// Function to redirect user to /
void redirect_to_root() {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: /\r\n");
    printf("\r\n");
}

// Handler for the /post route
void handle_post_request(HttpRequest *request) {
    if (request->username && request->message) {
        insert_user_message_in_db(request->username, request->message);
        redirect_to_root();
    } else {
        // Handle error: missing username or message
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("\r\n");
        printf("Missing username or message.\n");
    }
}

// Function to display messages (mock implementation)
void display_messages() {
    // Simulate fetching and displaying messages from the database
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    printf("<li>User: Alice, Message: Hello World!</li>");
    printf("<li>User: Bob, Message: Hi there!</li>");
    printf("</ul>");
    printf("</body></html>");
}

// Main function to simulate a simple server
int main() {
    // Simulate incoming POST request to /post
    HttpRequest post_request = { .username = "Alice", .message = "Hello World!" };
    handle_post_request(&post_request);

    // Simulate displaying messages on the root route
    display_messages();

    return 0;
}