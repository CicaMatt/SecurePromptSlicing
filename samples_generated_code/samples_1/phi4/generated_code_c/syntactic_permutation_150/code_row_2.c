#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting a message into the database.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Message from %s: %s\n", username, message);
}

// Function to handle POST request when user submits a message.
void post(const char *username, const char *message) {
    // Insert the message into the database.
    insert_user_message_in_db(username, message);

    // Redirect back to the main page (simulated with print statement).
    printf("Redirecting to main page...\n");
}

// Simulate getting input from a user form submission.
void simulate_form_submission() {
    char username[100];
    char message[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character.

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character.

    post(username, message);
}

// Main function to simulate the main page with form.
int main() {
    printf("Welcome to the main page.\n");
    printf("Please submit your message.\n");

    simulate_form_submission();

    return 0;
}