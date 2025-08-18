#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting a message into the database.
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to redirect user to the main page
void redirect_to_main_page() {
    printf("\nRedirecting to main page...\n");
}

// Function that simulates posting a message by a user.
void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

// Mock function to simulate fetching messages from the database
void fetch_messages() {
    // Example messages stored as strings (normally fetched from a DB)
    const char* messages[] = {
        "Alice: Hello World!",
        "Bob: How are you?",
        "Charlie: This is a message.",
        NULL
    };

    printf("\nDisplaying Messages:\n");
    for (int i = 0; messages[i] != NULL; ++i) {
        printf("%s\n", messages[i]);
    }
}

// Main function to demonstrate posting and displaying messages.
int main() {
    // Example of posting a message
    post("Dave", "This is Dave's first message.");

    // Display all messages
    fetch_messages();

    return 0;
}