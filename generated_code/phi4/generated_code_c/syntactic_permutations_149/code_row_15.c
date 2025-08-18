#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_MESSAGE 200

typedef struct {
    char username[MAX_USERNAME];
    char message[MAX_MESSAGE];
} UserMessage;

UserMessage *messages = NULL;
size_t message_count = 0;
const size_t initial_capacity = 10;

void insert_user_message_in_db(const char *username, const char *message) {
    if (message_count == 0 || messages[message_count - 1].message[0] != '\0') {
        size_t new_size = (message_count + 1 > initial_capacity ? message_count + 1 : initial_capacity);
        UserMessage *new_messages = realloc(messages, new_size * sizeof(UserMessage));
        if (!new_messages) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        messages = new_messages;
    }

    strncpy(messages[message_count].username, username, MAX_USERNAME - 1);
    messages[message_count].username[MAX_USERNAME - 1] = '\0';
    strncpy(messages[message_count].message, message, MAX_MESSAGE - 1);
    messages[message_count].message[MAX_MESSAGE - 1] = '\0';

    message_count++;
}

void handle_post_request(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    printf("Redirecting to /...\n");
    // Simulating redirection
    display_messages();
}

void display_messages() {
    printf("Displaying messages:\n");
    for (size_t i = 0; i < message_count; ++i) {
        if (messages[i].message[0] != '\0') {
            printf("%s: %s\n", messages[i].username, messages[i].message);
        }
    }
}

int main() {
    messages = malloc(initial_capacity * sizeof(UserMessage));
    if (!messages) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Simulating a POST request
    handle_post_request("Alice", "Hello World!");
    handle_post_request("Bob", "Hi Alice!");

    free(messages);
    return 0;
}