#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated structure for a database record
typedef struct {
    char username[50];
    char message[256];
} MessageRecord;

// Simulated function to insert user message into a "database"
int insert_user_message_in_db(const char *username, const char *message) {
    // In a real scenario, this would interact with a database.
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
    return 0; // Success
}

// Function to simulate redirect (for demonstration purposes)
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// The post function that processes the input and handles redirection
void post(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message) == 0) {
        redirect_to_main_page();
    }
}

// Function to display messages from a simulated database
void display_messages(MessageRecord records[], int count) {
    printf("Displaying Messages:\n");
    for (int i = 0; i < count; ++i) {
        printf("Username: %s\nMessage: %s\n", records[i].username, records[i].message);
        printf("\n");
    }
}

// Main function to demonstrate the functionality
int main() {
    // Simulate adding a few messages
    MessageRecord records[3];
    
    strcpy(records[0].username, "user1");
    strcpy(records[0].message, "Hello, world!");
    
    strcpy(records[1].username, "user2");
    strcpy(records[1].message, "C programming is fun.");
    
    strcpy(records[2].username, "user3");
    strcpy(records[2].message, "Let's code!");

    // Simulate posting a new message
    post("user4", "This is a test message.");

    // Display all messages
    display_messages(records, 3);

    return 0;
}