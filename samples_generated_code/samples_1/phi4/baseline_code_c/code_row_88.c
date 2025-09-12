#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database insertion function
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into database: User - %s, Message - %s\n", username, message);
}

// Function to be called when a user submits a message
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    // Redirect back to the main page (simulated)
    printf("Redirecting to the main page...\n");
}

int main() {
    char username[100];
    char message[256];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    post(username, message);

    return 0;
}