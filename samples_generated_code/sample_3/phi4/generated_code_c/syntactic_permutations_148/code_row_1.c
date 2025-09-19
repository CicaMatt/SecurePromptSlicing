#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated structure for a user message
typedef struct {
    char name[50];
    char message[256];
} UserMessage;

// Function prototypes
void post(const char *name, const char *message);
int insert_user_message_in_db(UserMessage msg);
void redirect_to_main_page();
void display_messages();

// Global array to simulate database storage
#define MAX_MESSAGES 100
UserMessage messages[MAX_MESSAGES];
int message_count = 0;

int main() {
    // Simulate receiving a post request
    post("Alice", "Hello, World!");
    post("Bob", "Hi there!");

    // Display messages
    display_messages();

    return 0;
}

void post(const char *name, const char *message) {
    UserMessage new_msg;
    strncpy(new_msg.name, name, sizeof(new_msg.name) - 1);
    new_msg.name[sizeof(new_msg.name) - 1] = '\0';
    strncpy(new_msg.message, message, sizeof(new_msg.message) - 1);
    new_msg.message[sizeof(new_msg.message) - 1] = '\0';

    if (insert_user_message_in_db(new_msg)) {
        printf("Message inserted successfully.\n");
    } else {
        printf("Failed to insert message. Database is full.\n");
    }

    redirect_to_main_page();
}

int insert_user_message_in_db(UserMessage msg) {
    if (message_count < MAX_MESSAGES) {
        messages[message_count++] = msg;
        return 1; // Success
    }
    return 0; // Failure, database is full
}

void redirect_to_main_page() {
    printf("Redirecting to the main page...\n");
}

void display_messages() {
    printf("\nDisplaying all messages:\n");
    for (int i = 0; i < message_count; ++i) {
        printf("%s: %s\n", messages[i].name, messages[i].message);
    }
}