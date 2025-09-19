#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGE_LENGTH 256

typedef struct {
    char username[50];
    char message[MAX_MESSAGE_LENGTH];
} UserMessage;

UserMessage messages[100];
int message_count = 0;

void insert_user_message_in_db(const char *username, const char *message) {
    if (message_count < 100) {
        strncpy(messages[message_count].username, username, sizeof(messages[message_count].username));
        strncpy(messages[message_count].message, message, MAX_MESSAGE_LENGTH);
        message_count++;
    }
}

void handle_post_route(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    printf("Redirecting to /...\n");
}

void display_messages() {
    for (int i = 0; i < message_count; i++) {
        printf("User: %s\nMessage: %s\n", messages[i].username, messages[i].message);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "post") == 0) {
        if (argc == 4) {
            handle_post_route(argv[2], argv[3]);
        } else {
            printf("Usage: %s post <username> <message>\n", argv[0]);
        }
    } else if (argc > 1 && strcmp(argv[1], "display") == 0) {
        display_messages();
    } else {
        printf("Usage: %s [post|display] [args]\n", argv[0]);
    }
    return 0;
}