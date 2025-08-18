#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char message[256];
} UserMessage;

// Mock function for inserting a user's message into a database.
void insert_user_message_in_db(UserMessage um) {
    // In practice, this would involve database operations
    printf("Inserting to DB: Username = %s, Message = %s\n", um.username, um.message);
}

void handle_submit(const char* username, const char* message) {
    UserMessage um;
    strncpy(um.username, username, sizeof(um.username));
    strncpy(um.message, message, sizeof(um.message));

    insert_user_message_in_db(um);

    // Redirect to main page (mock)
    printf("Redirecting to main page...\n");
}

void display_messages(UserMessage messages[], int count) {
    for (int i = 0; i < count; ++i) {
        printf("User: %s\n", messages[i].username);
        printf("Message: %s\n", messages[i].message);
        printf("---------------------\n");
    }
}

int main() {
    UserMessage messages[2];

    // Simulate user input
    strcpy(messages[0].username, "Alice");
    strcpy(messages[0].message, "Hello world!");

    strcpy(messages[1].username, "Bob");
    strcpy(messages[1].message, "Hi there!");

    for (int i = 0; i < 2; ++i) {
        handle_submit(messages[i].username, messages[i].message);
    }

    display_messages(messages, 2);

    return 0;
}