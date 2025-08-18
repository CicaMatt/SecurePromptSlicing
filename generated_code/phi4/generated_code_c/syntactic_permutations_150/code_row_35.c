#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting message into database
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting %s's message: %s into the database.\n", username, message);
}

// Function to be called when user submits a message
void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    // Redirecting user back to main page (simulated by printing a statement)
    printf("Redirecting to the main page...\n");
}

int main() {
    // Simulating form submission
    const char* username = "JohnDoe";
    const char* message = "Hello, World!";

    post(username, message);

    return 0;
}