#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple database as an array of strings.
#define MAX_MESSAGES 100
char messages[MAX_MESSAGES][256];
int message_count = 0;

void insert_user_message_in_db(const char *message) {
    if (message_count < MAX_MESSAGES) {
        strncpy(messages[message_count], message, sizeof(messages[message_count]) - 1);
        messages[message_count][sizeof(messages[message_count]) - 1] = '\0'; // Ensure null-termination
        message_count++;
        printf("Message inserted into the database.\n");
    } else {
        printf("Database is full. Cannot insert more messages.\n");
    }
}

void display_messages() {
    if (message_count == 0) {
        printf("No messages to display.\n");
    } else {
        for (int i = 0; i < message_count; ++i) {
            printf("%d: %s\n", i + 1, messages[i]);
        }
    }
}

void handle_post(const char *message) {
    insert_user_message_in_db(message);
    // Redirect to / route
    printf("Redirecting to /...\n");
    display_messages();
}

int main() {
    // Simulating a POST request with a message
    const char *user_message = "Hello, this is a test message!";
    
    handle_post(user_message);

    return 0;
}