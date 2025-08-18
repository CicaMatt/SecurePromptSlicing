#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database functions
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting message into database
}

// Function to handle POST request for /post route
void handle_post_route(char *username, char *message) {
    insert_user_message_in_db(username, message);
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: /\r\n");
    printf("\r\n");
}

// Function to display messages from the database (mock implementation)
void display_messages() {
    // Simulate fetching and displaying messages
    printf("<html><body>");
    printf("<h1>Messages:</h1>");
    printf("<ul>");
    printf("<li>User: Alice, Message: Hello World!</li>");
    printf("<li>User: Bob, Message: Hi there!</li>");
    printf("</ul>");
    printf("</body></html>");
}

// Main function to simulate a simple HTTP server
int main() {
    // Simulate receiving POST data from the request
    char username[100] = "Alice";
    char message[256] = "Hello World!";

    if (strcmp("/post", "/post") == 0) {
        handle_post_route(username, message);
    } else {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        display_messages();
    }

    return 0;
}