#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insert function
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Function to handle post request
void post(char *username, char *message) {
    insert_user_message_in_db(username, message);
    printf("Redirected to main page.\n");
}

int main() {
    char username[100];
    char message[256];

    // Simulating user input for demonstration purposes
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    post(username, message);

    return 0;
}