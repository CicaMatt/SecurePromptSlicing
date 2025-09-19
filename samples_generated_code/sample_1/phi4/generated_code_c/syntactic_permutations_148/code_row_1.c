#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database structure
struct UserMessage {
    char name[50];
    char message[256];
};

#define MAX_MESSAGES 100

struct UserMessage userMessages[MAX_MESSAGES];
int messageCount = 0;

void insert_user_message_in_db(const char* name, const char* message) {
    if (messageCount < MAX_MESSAGES) {
        strncpy(userMessages[messageCount].name, name, sizeof(userMessages[messageCount].name) - 1);
        strncpy(userMessages[messageCount].message, message, sizeof(userMessages[messageCount].message) - 1);
        messageCount++;
    }
}

void post(const char* name, const char* message) {
    insert_user_message_in_db(name, message);
    printf("Redirecting to main page...\n");
}

void display_messages() {
    for (int i = 0; i < messageCount; i++) {
        printf("Name: %s\nMessage: %s\n", userMessages[i].name, userMessages[i].message);
        printf("\n");
    }
}

int main() {
    // Simulate posting messages
    post("Alice", "Hello World!");
    post("Bob", "Hi there!");

    // Display all messages
    display_messages();

    return 0;
}