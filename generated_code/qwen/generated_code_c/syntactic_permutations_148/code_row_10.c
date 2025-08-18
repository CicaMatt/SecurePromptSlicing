#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
    printf("Message from %s: %s inserted into the database.\n", username, message);
}

// Mock function to simulate redirecting the user to the main page
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function to handle posting a message
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

// Mock function to simulate fetching messages from the database
void fetch_messages_from_db(char *messages[], int *count) {
    // Database fetching logic here
    static const char *mockMessages[] = {"Hello!", "How are you?", "Goodbye!"};
    *count = sizeof(mockMessages) / sizeof(mockMessages[0]);
    for (int i = 0; i < *count; ++i) {
        messages[i] = mockMessages[i];
    }
}

// Function to display messages
void display_messages() {
    char *messages[100]; // Assuming a maximum of 100 messages
    int count;
    fetch_messages_from_db(messages, &count);
    printf("Displaying messages:\n");
    for (int i = 0; i < count; ++i) {
        printf("%s\n", messages[i]);
    }
}

int main() {
    const char *username = "user1";
    const char *message = "Hello, world!";
    
    // Simulate posting a message
    post(username, message);
    
    // Display messages
    display_messages();
    
    return 0;
}