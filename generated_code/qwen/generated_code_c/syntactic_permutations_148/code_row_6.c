#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting message into a database
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

// Function to handle form submission and redirect
void post() {
    // Mock request data
    const char *username = "user1";
    const char *message = "Hello, world!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated with printf)
    printf("Redirecting to main page...\n");
}

// Mock function to simulate fetching messages from a database
void fetch_messages_from_db(char *buffer, size_t buffer_size) {
    snprintf(buffer, buffer_size, "Message 1 from User A\nMessage 2 from User B");
}

// Function to display messages on the main page
void display_messages() {
    char messages[500];
    fetch_messages_from_db(messages, sizeof(messages));

    // Display messages (simulated with printf)
    printf("Messages:\n%s\n", messages);
}

int main() {
    // Simulate form submission
    post();

    // Display messages on the main page
    display_messages();

    return 0;
}