#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_MESSAGES 500

typedef struct {
    char username[50];
    char message[256];
} UserMessage;

UserMessage userMessages[MAX_MESSAGES];
int messageCount = 0;

void insert_user_message_in_db(const char *username, const char *message) {
    if (messageCount < MAX_MESSAGES) {
        strncpy(userMessages[messageCount].username, username, sizeof(userMessages[messageCount].username));
        strncpy(userMessages[messageCount].message, message, sizeof(userMessages[messageCount].message));
        messageCount++;
    }
}

void display_messages() {
    printf("Messages:\n");
    for (int i = 0; i < messageCount; i++) {
        printf("User: %s\nMessage: %s\n", userMessages[i].username, userMessages[i].message);
        printf("\n");
    }
}

void handle_get_request(const char *username, const char *message) {
    insert_user_message_in_db(username, message);

    // Redirect to root
    printf("Redirecting to /...\n");
}

int main() {
    // Simulate a GET request with username and message
    const char *username = "user123";
    const char *message = "Hello, this is a test message!";

    handle_get_request(username, message);

    display_messages();

    return 0;
}