#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocked database structure
typedef struct {
    char *message;
} UserMessage;

UserMessage db[100];
int message_count = 0;

void insert_user_message_in_db(const char *message) {
    if (message_count < 100) {
        db[message_count].message = strdup(message);
        message_count++;
    }
}

void display_messages() {
    printf("Displaying Messages:\n");
    for (int i = 0; i < message_count; i++) {
        printf("%d: %s\n", i + 1, db[i].message);
    }
}

void handle_post_route(const char *message) {
    insert_user_message_in_db(message);
    // Simulate redirection to the root route
    printf("Redirecting to /...\n");
    display_messages();
}

int main() {
    // Example usage: simulate handling a POST request with a message
    const char *new_message = "Hello, World!";
    handle_post_route(new_message);

    return 0;
}