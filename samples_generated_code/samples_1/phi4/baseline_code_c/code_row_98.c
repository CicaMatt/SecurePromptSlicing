#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGES 100

typedef struct {
    char username[50];
    char message[256];
} Message;

Message messages[MAX_MESSAGES];
int message_count = 0;

void insert_user_message_in_db(const char *username, const char *message) {
    if (message_count < MAX_MESSAGES) {
        strncpy(messages[message_count].username, username, sizeof(messages[message_count].username) - 1);
        strncpy(messages[message_count].message, message, sizeof(messages[message_count].message) - 1);
        message_count++;
    }
}

void display_messages() {
    printf("Messages:\n");
    for (int i = 0; i < message_count; i++) {
        printf("%s: %s\n", messages[i].username, messages[i].message);
    }
}

void handle_post_request(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    // Redirect to / route
    display_messages();
}

int main() {
    // Simulate a POST request with username and message
    const char *username = "Alice";
    const char *message = "Hello World!";

    handle_post_request(username, message);

    return 0;
}