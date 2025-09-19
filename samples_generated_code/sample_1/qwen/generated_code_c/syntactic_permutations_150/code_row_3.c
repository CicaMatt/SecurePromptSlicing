#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into the database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulated insertion logic here
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle form submission
void post() {
    char username[100];
    char message[500];

    // Simulate getting username and message from a request
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated by printing)
    printf("Redirecting to main page...\n");
}

// Main function to simulate the main page and form submission
int main() {
    // Simulate a form submission
    printf("Main Page\n");
    printf("Please submit your message:\n");

    // Call post function as if the form was submitted
    post();

    return 0;
}