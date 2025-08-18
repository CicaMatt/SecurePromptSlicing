#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structure for a database record
typedef struct {
    char username[50];
    char message[256];
} UserMessage;

// Function prototypes
void insert_user_message_in_db(const char *username, const char *message);
void define();
void display_messages();

int main() {
    // Simulate user submitting a message
    define("Alice", "Hello, World!");
    
    // Display messages
    display_messages();
    
    return 0;
}

// Mock function to insert a message into the database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
}

// Function called when user submits a message
void define(const char *username, const char *message) {
    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated by calling display_messages)
    display_messages();
}

// Mock function to display messages from the database
void display_messages() {
    // Example data that would be fetched from a real database
    UserMessage dbMessages[] = {
        {"Alice", "Hello, World!"},
        {"Bob", "Hi there!"},
        {"Charlie", "Good morning!"}
    };
    
    int numMessages = sizeof(dbMessages) / sizeof(UserMessage);

    printf("Displaying Messages:\n");
    for (int i = 0; i < numMessages; ++i) {
        printf("%s: %s\n", dbMessages[i].username, dbMessages[i].message);
    }
}