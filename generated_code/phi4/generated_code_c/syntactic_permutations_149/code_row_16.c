#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *message;
} UserMessage;

UserMessage *user_messages = NULL;
int message_count = 0;
const int max_user_messages = 100;

void insert_user_message_in_db(const char *username, const char *message) {
    if (message_count < max_user_messages) {
        user_messages = realloc(user_messages, (message_count + 1) * sizeof(UserMessage));
        UserMessage new_message = { strdup(username), strdup(message) };
        user_messages[message_count++] = new_message;
    }
}

void display_messages() {
    printf("Messages:\n");
    for (int i = 0; i < message_count; ++i) {
        printf("%s: %s\n", user_messages[i].username, user_messages[i].message);
    }
}

void handle_post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    display_messages();
}

int main() {
    // Simulating a POST request to /post
    handle_post("alice", "Hello, World!");
    handle_post("bob", "Hi there!");

    free(user_messages);

    return 0;
}