#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting a message into a database
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle the post request
void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    // Redirect to main page (simulated with a print statement)
    printf("Redirecting to main page...\n");
}

// Mock function to simulate fetching messages from the database
void fetch_messages_from_db(char*** messages, int* count) {
    static char* mockMessages[] = {"Hello, World!", "This is a test.", "Another message."};
    *messages = mockMessages;
    *count = sizeof(mockMessages) / sizeof(mockMessages[0]);
}

// Function to display messages
void display_messages() {
    char** messages;
    int count;
    fetch_messages_from_db(&messages, &count);
    
    printf("Displaying messages:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", messages[i]);
    }
}

// Main function to simulate the flow
int main() {
    // Simulate a post request with a username and message
    const char* username = "user123";
    const char* message = "Hello, this is my first message!";
    post(username, message);
    
    // Display messages after posting
    display_messages();
    
    return 0;
}