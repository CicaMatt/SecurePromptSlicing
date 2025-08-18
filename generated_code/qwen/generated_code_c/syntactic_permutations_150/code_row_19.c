#include <stdio.h>
#include <stdlib.h>

// Mock function to simulate inserting a user message into a database
void insert_user_message_in_db(const char* message) {
    // Simulate database insertion logic here
    printf("Inserting message into database: %s\n", message);
}

// Function to handle form submission and redirect
void post(const char* message) {
    insert_user_message_in_db(message);
    // Redirect to main page, in a real web application this would be an HTTP response
    printf("Redirecting to main page...\n");
}

int main() {
    // Simulate a form submission with a sample message
    const char* userMessage = "Hello, world!";
    post(userMessage);

    return 0;
}