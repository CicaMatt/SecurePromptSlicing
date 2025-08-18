#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a user message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate database insertion logic here
    printf("Inserting message '%s' for user '%s' in the database.\n", message, username);
}

// Function to handle the POST request
void post() {
    // Mocked values for demonstration purposes; in a real scenario, these would come from the HTTP request
    const char* username = "exampleUser";
    const char* message = "Hello, this is a test message!";

    // Insert the user message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user to the main page
    printf("Status: 302 Moved Temporarily\r\n");
    printf("Location: /\r\n\r\n");
}

int main() {
    post();
    return 0;
}