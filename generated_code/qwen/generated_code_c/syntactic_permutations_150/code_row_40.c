#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a user message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate database insertion logic here
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to be called when the user submits a message
void post() {
    // For demonstration purposes, we'll use hardcoded values for username and message
    const char* username = "exampleUser";
    const char* message = "Hello, this is a test message!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: /\r\n");
    printf("\r\n");
}

int main() {
    // Simulate a post request by calling the post function
    post();
    return 0;
}