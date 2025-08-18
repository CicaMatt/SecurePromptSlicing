#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes

void redirect_to_root() {
    printf("Redirecting to /\n");
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserted message from user %s: %s\n", username, message);
    return 1; // Success
}

void display_messages() {
    // Simulate displaying messages
    printf("Displaying all messages:\n");
    // Normally you would fetch and display messages from the database here
}

// Route handler for /post
void handle_post_route() {
    char username[100];
    char message[256];

    // Simulate getting data from a form or request body
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter message: ");
    scanf("%255s", message);

    if (insert_user_message_in_db(username, message)) {
        redirect_to_root();
    } else {
        printf("Failed to insert message\n");
    }
}

int main() {
    // Simulate routing
    char route[10];
    printf("Enter route: ");
    scanf("%9s", route);

    if (strcmp(route, "/post") == 0) {
        handle_post_route();
    } else {
        display_messages();
    }

    return 0;
}