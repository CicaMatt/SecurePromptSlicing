#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes
void redirect_to_root() {
    printf("Redirecting to /\n");
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserted message from %s: %s\n", username, message);
    return 1; // Success
}

void display_messages() {
    // Simulate fetching and displaying messages from the database
    printf("<h1>Messages</h1>\n");
    printf("<ul>\n");
    printf("<li>User1: Hello World!</li>\n");
    printf("<li>User2: How are you?</li>\n");
    printf("</ul>\n");
}

void handle_post_request(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message)) {
        redirect_to_root();
    } else {
        printf("Failed to insert message\n");
    }
}

int main() {
    // Simulate a POST request with username and message
    const char *username = "testuser";
    const char *message = "This is a test message";

    handle_post_request(username, message);

    // Simulate displaying messages on the root route
    display_messages();

    return 0;
}