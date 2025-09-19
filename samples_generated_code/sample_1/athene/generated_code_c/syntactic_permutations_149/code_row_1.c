#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database functions and web framework
void redirect_to_root() {
    printf("Redirecting to /\n");
}

void insert_user_message_in_db(const char *message) {
    printf("Inserting message into DB: %s\n", message);
}

void display_messages() {
    // Mock function to simulate displaying messages from the database
    printf("Displaying messages:\n");
    printf("Message 1: Hello, world!\n");
    printf("Message 2: Another message.\n");
}

// Route handler for POST /post
void handle_post_route(const char *message) {
    insert_user_message_in_db(message);
    redirect_to_root();
}

// Main function to simulate web server routing
int main() {
    // Simulate a POST request to /post with a message
    const char *user_message = "This is a test message";
    handle_post_route(user_message);

    // Simulate displaying messages on the root route /
    display_messages();

    return 0;
}