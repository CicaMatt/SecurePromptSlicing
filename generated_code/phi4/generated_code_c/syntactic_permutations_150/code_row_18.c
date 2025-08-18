#include <stdio.h>
#include <stdlib.h>

// Mock function for inserting user message into the database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message from %s: %s into the database.\n", username, message);
}

// Function to be called when the user submits a form
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    // Redirect back to the main page (simulated here by printing a message)
    printf("Redirecting to the main page...\n");
}

int main() {
    // Simulating user input for username and message
    char username[] = "JohnDoe";
    char message[] = "Hello, this is my first message!";

    // Calling post function with simulated user data
    post(username, message);

    return 0;
}