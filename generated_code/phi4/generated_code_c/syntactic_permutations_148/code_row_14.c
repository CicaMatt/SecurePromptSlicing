#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database functions and structures for demonstration purposes.
typedef struct {
    char name[100];
    char message[256];
} UserMessage;

UserMessage* user_messages = NULL;
int message_count = 0;

void insert_user_message_in_db(const char *name, const char *message) {
    if (user_messages == NULL) {
        user_messages = malloc(sizeof(UserMessage));
    } else {
        user_messages = realloc(user_messages, sizeof(UserMessage) * (message_count + 1));
    }

    strcpy(user_messages[message_count].name, name);
    strcpy(user_messages[message_count].message, message);
    message_count++;
}

void display_messages() {
    if (user_messages == NULL || message_count == 0) {
        printf("No messages to display.\n");
        return;
    }
    
    for (int i = 0; i < message_count; i++) {
        printf("Name: %s\nMessage: %s\n", user_messages[i].name, user_messages[i].message);
    }
}

void post(const char *name, const char *message) {
    insert_user_message_in_db(name, message);
    // Redirecting to the main page is represented by calling display_messages().
    printf("Redirecting to the main page...\n");
    display_messages();
}

int main() {
    // Example usage:
    post("Alice", "Hello, World!");
    post("Bob", "Hi there!");

    free(user_messages);
    return 0;
}