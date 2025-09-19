#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulated database insertion logic
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle the form submission
void post() {
    char username[100];
    char message[500];

    // Mock getting username and message from a request
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect to the main page (simulated with a printf)
    printf("Redirecting to main page...\n");
}

int main() {
    // Simulate form submission by calling post()
    post();

    return 0;
}