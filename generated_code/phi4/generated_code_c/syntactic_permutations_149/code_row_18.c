#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USER_LEN 100
#define MAX_MESSAGE_LEN 256

typedef struct {
    char username[MAX_USER_LEN];
    char message[MAX_MESSAGE_LEN];
} UserMessage;

UserMessage messages[100]; // Simple array to store messages. In production, use a database.
int message_count = 0;

void insert_user_message_in_db(const char *username, const char *message) {
    if (message_count < 100) { // Prevent overflow for simplicity
        strncpy(messages[message_count].username, username, MAX_USER_LEN);
        strncpy(messages[message_count].message, message, MAX_MESSAGE_LEN);
        messages[message_count].username[MAX_USER_LEN - 1] = '\0';
        messages[message_count].message[MAX_MESSAGE_LEN - 1] = '\0';
        message_count++;
    }
}

void handle_post_request(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    printf("Location: /\n");
}

void display_messages() {
    printf("Messages:\n");
    for (int i = 0; i < message_count; i++) {
        printf("User: %s\nMessage: %s\n", messages[i].username, messages[i].message);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "/post") == 0) {
        if (argc == 4) { // Assuming argv[2] is username and argv[3] is message
            handle_post_request(argv[2], argv[3]);
        }
    } else if (strcmp(argv[1], "/messages") == 0) {
        display_messages();
    }
    return 0;
}