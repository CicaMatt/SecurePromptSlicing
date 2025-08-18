#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into a database
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

// Function to handle the post request
void post() {
    // Mock retrieval of username and message from request
    const char* username = "exampleUser";
    const char* message = "Hello, this is a test message!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated with printf)
    printf("Redirecting to main page...\n");
}

int main() {
    // Simulate a post request
    post();
    return 0;
}