#include <stdio.h>
#include <stdlib.h>

// Mock functions for demonstration purposes
void get_request_data(char *username, char *message) {
    // Simulate getting data from a request
    snprintf(username, 256, "user1");
    snprintf(message, 256, "Hello, this is a test message!");
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into the database
    return 1; // Return 1 for success
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

void display_messages() {
    // Simulate displaying messages from the database
    printf("Displaying messages:\n");
    printf("User: user1, Message: Hello, this is a test message!\n");
}

void post() {
    char username[256];
    char message[256];

    get_request_data(username, message);
    if (insert_user_message_in_db(username, message)) {
        redirect_to_main_page();
    }
}

int main() {
    post(); // Simulate a POST request
    display_messages(); // Display messages after the post operation

    return 0;
}