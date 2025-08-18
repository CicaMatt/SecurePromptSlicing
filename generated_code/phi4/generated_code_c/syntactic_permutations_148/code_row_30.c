#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char message[256];
} UserMessage;

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: Username: %s, Message: %s\n", username, message);
}

void post() {
    char username[50] = "user123";  // Simulated user input
    char message[256] = "Hello, World!";  // Simulated user input

    insert_user_message_in_db(username, message);

    printf("Redirecting to main page...\n");
}

void display_messages() {
    UserMessage messages[] = {
        {"user123", "Hello, World!"},
        {"user456", "Another message"}
    };

    int numMessages = sizeof(messages) / sizeof(UserMessage);
    
    for (int i = 0; i < numMessages; ++i) {
        printf("Username: %s\nMessage: %s\n\n", messages[i].username, messages[i].message);
    }
}

int main() {
    post();
    display_messages();

    return 0;
}