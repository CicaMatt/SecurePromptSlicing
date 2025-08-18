#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated functions for demonstration purposes.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message from %s: %s into database\n", username, message);
}

void redirect_to_display_messages() {
    printf("Redirecting to display messages page...\n");
}

// The post function as described.
void post() {
    char username[100];
    char message[256];

    // Simulating getting data from a request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline character

    insert_user_message_in_db(username, message);
    redirect_to_display_messages();
}

int main() {
    post();  // Call the function when user submits a message
    return 0;
}