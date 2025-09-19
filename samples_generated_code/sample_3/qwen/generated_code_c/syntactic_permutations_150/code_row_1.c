#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulated database insertion logic
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to handle the submission of a message
void post() {
    char username[100];
    char message[500];

    // For demonstration purposes, we'll manually set these values.
    // In a real scenario, you would retrieve these from an HTTP request.
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    // Insert the user's message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("Redirecting to main page...\n");
}

int main() {
    // Simulate a post request by calling the post function
    post();
    return 0;
}