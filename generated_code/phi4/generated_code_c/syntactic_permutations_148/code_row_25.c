#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a database with an array of structures
#define MAX_MESSAGES 100

typedef struct {
    char username[50];
    char message[256];
} Message;

Message messageDatabase[MAX_MESSAGES];
int messageCount = 0;

void insert_user_message_in_db(const char *username, const char *message) {
    if (messageCount < MAX_MESSAGES) {
        strncpy(messageDatabase[messageCount].username, username, sizeof(messageDatabase[messageCount].username));
        strncpy(messageDatabase[messageCount].message, message, sizeof(messageDatabase[messageCount].message));
        messageCount++;
    }
}

void redirect_to_main_page() {
    printf("Redirecting to the main page...\n");
}

void post(const char *username, const char *user_message) {
    insert_user_message_in_db(username, user_message);
    redirect_to_main_page();
}

void display_messages() {
    printf("Displaying messages:\n");
    for (int i = 0; i < messageCount; i++) {
        printf("Username: %s\nMessage: %s\n", messageDatabase[i].username, messageDatabase[i].message);
    }
}

int main() {
    // Example usage
    post("user1", "Hello, World!");
    post("user2", "Another message");

    display_messages();

    return 0;
}