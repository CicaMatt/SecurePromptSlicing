#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_MESSAGE_LEN 256

typedef struct {
    char username[MAX_USERNAME_LEN];
    char message[MAX_MESSAGE_LEN];
} UserMessage;

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserting into DB: %s - %s\n", username, message);
    return 1; // Return 1 on success
}

void display_messages() {
    UserMessage messages[] = {
        {"alice", "Hello World!"},
        {"bob", "Hi there!"},
        {"charlie", "How's it going?"}
    };
    int num_messages = sizeof(messages) / sizeof(UserMessage);
    
    printf("Messages:\n");
    for (int i = 0; i < num_messages; ++i) {
        printf("%s: %s\n", messages[i].username, messages[i].message);
    }
}

void handle_post_route(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message)) {
        printf("Redirecting to / route...\n");
        // Simulate redirection by displaying the main page content
        display_messages();
    } else {
        printf("Failed to insert message.\n");
    }
}

int main() {
    char username[MAX_USERNAME_LEN] = "dave";
    char message[MAX_MESSAGE_LEN] = "This is a test message.";
    
    handle_post_route(username, message);
    
    return 0;
}