#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate database insertion logic here
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle the post action
void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    // Redirect to main page
    printf("Redirecting to main page...\n");
}

// Mock function to simulate fetching messages from a database
void fetch_messages_from_db(char*** messages, int* count) {
    // Simulate fetching messages logic here
    *count = 3;
    *messages = (char**)malloc(*count * sizeof(char*));
    (*messages)[0] = strdup("User1: Hello");
    (*messages)[1] = strdup("User2: Hi there!");
    (*messages)[2] = strdup("User1: How are you?");
}

// Function to display messages
void display_messages() {
    char** messages;
    int count;
    fetch_messages_from_db(&messages, &count);

    printf("Messages:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", messages[i]);
        free(messages[i]);
    }
    free(messages);
}

int main() {
    // Example usage of post function
    post("User1", "Hello, world!");

    // Display messages
    display_messages();

    return 0;
}