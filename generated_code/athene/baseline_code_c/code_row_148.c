#include <stdio.h>
#include <stdlib.h>

// Mock functions for demonstration purposes
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserted message from %s: %s\n", username, message);
    return 1; // Return success
}

void display_messages() {
    // Mock function to simulate displaying messages
    printf("Displaying messages...\n");
    printf("Message 1: Hello, world!\n");
    printf("Message 2: How are you?\n");
}

void post(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message)) {
        redirect_to_main_page();
    } else {
        printf("Failed to insert message.\n");
    }
}

int main() {
    // Simulate a POST request with username and message
    const char *username = "user1";
    const char *message = "Hello, this is a test message!";

    post(username, message);

    // Display messages after posting
    display_messages();

    return 0;
}