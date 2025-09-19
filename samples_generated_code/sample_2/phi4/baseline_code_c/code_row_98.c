#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_MESSAGES 1000

typedef struct {
    char username[50];
    char message[256];
} Message;

Message userMessages[MAX_MESSAGES];
int messageCount = 0;

void insert_user_message_in_db(const char* username, const char* message) {
    if (messageCount < MAX_MESSAGES) {
        strncpy(userMessages[messageCount].username, username, sizeof(userMessages[messageCount].username));
        strncpy(userMessages[messageCount].message, message, sizeof(userMessages[messageCount].message));
        messageCount++;
    }
}

void display_messages() {
    for (int i = 0; i < messageCount; i++) {
        printf("User: %s\nMessage: %s\n", userMessages[i].username, userMessages[i].message);
        printf("-----------------------------------\n");
    }
}

void handle_post_request(const char* username, const char* message) {
    insert_user_message_in_db(username, message);

    // Redirect to / route (simulated by calling display_messages)
    printf("Redirecting to /...\n");
    display_messages();
}

int main() {
    // Simulate handling a POST request
    handle_post_request("Alice", "Hello, World!");
    handle_post_request("Bob", "Hi there!");

    return 0;
}