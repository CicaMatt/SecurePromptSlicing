#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_MESSAGE_LENGTH 256

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char message[MAX_MESSAGE_LENGTH];
} UserMessage;

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion (In real case, this function would interact with a database)
    printf("Inserting into DB: Username=%s, Message=%s\n", username, message);
    return 1; // Success
}

void display_messages(UserMessage messages[], int count) {
    for (int i = 0; i < count; ++i) {
        printf("%s: %s\n", messages[i].username, messages[i].message);
    }
}

void handle_post(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message)) {
        printf("Redirecting to /\n");
    } else {
        fprintf(stderr, "Failed to insert message\n");
    }
}

int main() {
    UserMessage messages[10]; // Example storage for messages
    int message_count = 0;

    const char *username = "test_user";
    const char *message = "Hello, this is a test message.";

    handle_post(username, message);

    strcpy(messages[message_count].username, username);
    strcpy(messages[message_count].message, message);
    ++message_count;

    printf("Displaying all messages:\n");
    display_messages(messages, message_count);

    return 0;
}