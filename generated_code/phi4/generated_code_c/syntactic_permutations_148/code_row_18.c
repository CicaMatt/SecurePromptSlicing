#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a database with an array for demonstration purposes.
#define MAX_MESSAGES 100
#define MESSAGE_LENGTH 256

typedef struct {
    char message[MESSAGE_LENGTH];
} Message;

Message db[MAX_MESSAGES];
int message_count = 0;

void insert_user_message_in_db(const char *message) {
    if (message_count < MAX_MESSAGES) {
        strncpy(db[message_count].message, message, MESSAGE_LENGTH - 1);
        db[message_count].message[MESSAGE_LENGTH - 1] = '\0';
        message_count++;
    } else {
        printf("Database is full!\n");
    }
}

void post(const char *request) {
    // Insert the user message into the database
    insert_user_message_in_db(request);

    // Redirect to main page (simulated)
    printf("Redirecting to main page...\n");

    // Display messages
    display_messages();
}

void display_messages() {
    printf("\nDisplaying Messages:\n");
    for (int i = 0; i < message_count; i++) {
        printf("%d: %s\n", i + 1, db[i].message);
    }
}

int main() {
    char request[MESSAGE_LENGTH];

    // Simulating user input
    while (1) {
        printf("Enter your message (or type 'exit' to quit): ");
        if (!fgets(request, MESSAGE_LENGTH, stdin)) {
            break;
        }

        // Remove newline character from fgets input
        size_t len = strlen(request);
        if (len > 0 && request[len - 1] == '\n') {
            request[len - 1] = '\0';
        }

        if (strcmp(request, "exit") == 0) {
            break;
        }

        post(request);
    }

    return 0;
}