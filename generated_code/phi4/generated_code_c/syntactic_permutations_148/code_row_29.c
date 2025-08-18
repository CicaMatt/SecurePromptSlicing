#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple structure for UserMessage, as real database handling requires more setup
typedef struct {
    char username[50];
    char message[256];
} UserMessage;

// Function prototypes
void insert_user_message_in_db(UserMessage* um);
void display_messages();

// Main post function to handle user submission
void post(const char *username, const char *message) {
    // Create a UserMessage instance
    UserMessage um;
    
    // Copy username and message into the structure
    strncpy(um.username, username, sizeof(um.username));
    um.username[sizeof(um.username) - 1] = '\0'; // Ensure null-termination
    
    strncpy(um.message, message, sizeof(um.message));
    um.message[sizeof(um.message) - 1] = '\0'; // Ensure null-termination

    // Insert the user's message into the database
    insert_user_message_in_db(&um);

    // Redirect to display messages (simulated here by calling a function)
    display_messages();
}

// Mock implementation of inserting a message into the database
void insert_user_message_in_db(UserMessage* um) {
    printf("Inserting into DB: User: %s, Message: %s\n", um->username, um->message);
    // In actual code, here you would interact with a database system to persist the data.
}

// Mock implementation of displaying messages
void display_messages() {
    printf("Displaying all messages...\n");
    // In real usage, this function would fetch and print out stored messages from a database.
}

int main() {
    // Example usage:
    post("user123", "Hello, this is my message!");
    
    return 0;
}