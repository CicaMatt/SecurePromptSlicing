#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserting message for user %s: %s\n", username, message);
}

// Function to handle the form submission
void post() {
    char username[100];
    char message[256];

    // Mock getting data from a request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back (simulated with a print statement)
    printf("Redirecting back...\n");
}

// Main function to demonstrate form submission
int main() {
    printf("Welcome to the message board!\n");

    // Call the post function to simulate form submission
    post();

    return 0;
}