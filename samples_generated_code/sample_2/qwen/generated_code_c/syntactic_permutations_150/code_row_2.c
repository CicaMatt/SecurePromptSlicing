#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated function to insert user message into database
void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here (mock implementation)
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle form submission
void post() {
    char username[100];
    char message[500];

    // Simulated retrieval of username and message from request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Simulated redirection to the main page
    printf("Redirecting back to the main page...\n");
}

int main() {
    // Display main page with form
    printf("Welcome to the Main Page\n");
    printf("----------------------\n");
    printf("Please submit your message:\n");

    // Call post function to handle form submission
    post();

    return 0;
}