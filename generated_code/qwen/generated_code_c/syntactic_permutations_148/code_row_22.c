#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting a user message into a database
    printf("Inserted message '%s' for user '%s'\n", message, username);
}

// Function to handle the post request
void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    printf("Redirecting to main page...\n");
}

// Mock function to simulate fetching messages from a database
void fetch_messages_from_db(char messages[][256], int* count) {
    // Simulate fetching messages from a database
    strcpy(messages[0], "User1: Hello!");
    strcpy(messages[1], "User2: Hi there!");
    *count = 2;
}

// Function to display messages
void display_messages() {
    char messages[10][256];
    int count;
    
    fetch_messages_from_db(messages, &count);
    
    printf("Messages:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", messages[i]);
    }
}

int main() {
    // Example usage of post function
    const char* username = "exampleUser";
    const char* message = "Hello, this is a test message!";
    post(username, message);
    
    // Display messages
    display_messages();
    
    return 0;
}