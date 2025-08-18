#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structure for demonstration purposes.
typedef struct {
    char username[50];
    char message[256];
} Message;

// Placeholder function for inserting a user message into a database.
void insert_user_message_in_db(const char *username, const char *message) {
    // For demonstration purposes, we'll just print the insertion action.
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
}

// Function to simulate redirecting to a main page.
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Mock function to get data from the request (for demonstration purposes).
int post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
    return 0;
}

// Function to display messages.
void display_messages(Message messages[], int count) {
    for (int i = 0; i < count; ++i) {
        printf("Username: %s\nMessage: %s\n", messages[i].username, messages[i].message);
    }
}

int main() {
    // Example usage of the post function
    const char *username = "Alice";
    const char *message = "Hello, world!";
    
    post(username, message);

    // Mock data for displaying messages
    Message mockMessages[] = {
        {"Bob", "Hi there!"},
        {"Charlie", "How are you?"},
        {"Dave", "Good morning!"}
    };
    int messageCount = sizeof(mockMessages) / sizeof(Message);
    
    display_messages(mockMessages, messageCount);

    return 0;
}