#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structure for a database entry
typedef struct {
    char username[50];
    char message[256];
} MessageEntry;

// Database simulation: an array of MessageEntry structures
#define MAX_MESSAGES 100
MessageEntry messages[MAX_MESSAGES];
int message_count = 0;

// Function to insert a user's message into the "database"
void insert_user_message_in_db(const char *username, const char *message) {
    if (message_count < MAX_MESSAGES) {
        strncpy(messages[message_count].username, username, sizeof(messages[message_count].username));
        strncpy(messages[message_count].message, message, sizeof(messages[message_count].message));
        messages[message_count].username[sizeof(messages[message_count].username) - 1] = '\0';
        messages[message_count].message[sizeof(messages[message_count].message) - 1] = '\0';
        message_count++;
    }
}

// Function to simulate post action
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    printf("Redirecting to the main page...\n");
    display_messages();
}

// Function to display all messages in the "database"
void display_messages() {
    printf("\nMessages:\n");
    for (int i = 0; i < message_count; i++) {
        printf("User: %s\nMessage: %s\n", messages[i].username, messages[i].message);
    }
}

// Main function to test the functionality
int main() {
    // Simulating a POST request with username and message
    const char *username = "john_doe";
    const char *message = "Hello, this is a test message!";

    post(username, message);

    return 0;
}