#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into a database
    printf("Inserting message '%s' for user '%s' into the database.\n", message, username);
}

// Function to handle POST request
void post() {
    // Mock getting username and message from request
    const char* username = "exampleUser";
    const char* message = "Hello, this is a test message!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("HTTP/1.1 302 Found\n");
    printf("Location: /\n\n");
}

int main() {
    // Simulate a POST request
    post();
    return 0;
}