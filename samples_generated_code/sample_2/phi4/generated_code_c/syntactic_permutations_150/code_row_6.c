#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting a user message into the database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to handle post request
void post(const char *username, const char *message) {
    // Insert user message into the database
    insert_user_message_in_db(username, message);

    // Redirect user back (simulated by printing a message)
    printf("Redirecting user back...\n");
}

int main() {
    // Simulate form data submission
    char username[100] = "user123";
    char message[256] = "Hello, this is a test message!";

    // Call post function to handle the request
    post(username, message);

    return 0;
}