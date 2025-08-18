#include <stdio.h>
#include <stdlib.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into database: Username = %s, Message = %s\n", username, message);
}

// Function called when the user submits a message
void handle_submit(const char *username, const char *message) {
    insert_user_message_in_db(username, message);

    // Simulating redirection to main page
    printf("Redirecting to main page...\n");
}

int main() {
    // Example usage
    const char *exampleUsername = "User123";
    const char *exampleMessage = "Hello, this is a test message!";

    handle_submit(exampleUsername, exampleMessage);

    return 0;
}