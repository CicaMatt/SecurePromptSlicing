#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating database insertion for demonstration purposes
int insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    printf("Message: %s\n", message);
    return 1; // Return 1 on success
}

void post() {
    char username[100];
    char message[256];

    // Simulating getting data from request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    if (insert_user_message_in_db(username, message)) {
        printf("Message posted successfully!\n");
    } else {
        printf("Failed to post message.\n");
    }

    // Simulating redirection back to the main page
    printf("Redirecting to main page...\n");
}

int main() {
    post();
    return 0;
}