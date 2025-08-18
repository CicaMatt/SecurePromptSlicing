#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a username and message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Message inserted for user '%s': %s\n", username, message);
}

// Function to handle the post request
void post(char *username, char *message) {
    insert_user_message_in_db(username, message);
    // Redirecting back to main page (simulated by printing a redirect statement)
    printf("Redirecting to main page...\n");
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