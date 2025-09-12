#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated structures for demonstration purposes
typedef struct {
    char name[100];
    char message[256];
} UserMessage;

// Function prototypes
void post(const char *name, const char *message);
int insert_user_message_in_db(UserMessage userMsg);
void redirect_to_main_page();
void display_messages();

// Global array to simulate database storage
#define MAX_MESSAGES 100
UserMessage messages[MAX_MESSAGES];
int message_count = 0;

int main() {
    // Simulate a post request with name and message
    const char *name = "Alice";
    const char *message = "Hello, World!";
    post(name, message);

    // Display all messages
    display_messages();

    return 0;
}

void post(const char *name, const char *message) {
    UserMessage userMsg;
    strncpy(userMsg.name, name, sizeof(userMsg.name) - 1);
    strncpy(userMsg.message, message, sizeof(userMsg.message) - 1);

    if (insert_user_message_in_db(userMsg)) {
        redirect_to_main_page();
    }
}

int insert_user_message_in_db(UserMessage userMsg) {
    if (message_count < MAX_MESSAGES) {
        messages[message_count++] = userMsg;
        return 1; // Success
    }
    return 0; // Failure due to reaching max capacity
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
    display_messages();
}

void display_messages() {
    printf("Displaying all messages:\n");
    for (int i = 0; i < message_count; ++i) {
        printf("Name: %s\nMessage: %s\n\n", messages[i].name, messages[i].message);
    }
}