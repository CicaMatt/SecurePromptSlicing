#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes
void redirect_to_root() {
    printf("Redirecting to /\n");
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserting message from user %s: %s\n", username, message);
    return 1; // Success
}

void display_messages() {
    // Simulate displaying messages
    printf("Displaying messages:\n");
    printf("User1: Message1\n");
    printf("User2: Message2\n");
}

void handle_new_message_route(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message)) {
        redirect_to_root();
    } else {
        printf("Failed to insert message into database.\n");
    }
}

int main() {
    const char *username = "testuser";
    const char *message = "Hello, World!";

    handle_new_message_route(username, message);
    display_messages();

    return 0;
}