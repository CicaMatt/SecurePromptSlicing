#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting a message into a database
    printf("Inserting user '%s' with message: %s\n", username, message);
}

// Function to simulate redirecting the user
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function called when the user submits a message
void post(const char *username, const char *message) {
    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user to the main page
    redirect_to_main_page();
}

int main() {
    // Example usage of the post function
    const char *username = "user123";
    const char *message = "Hello, world!";

    post(username, message);

    return 0;
}