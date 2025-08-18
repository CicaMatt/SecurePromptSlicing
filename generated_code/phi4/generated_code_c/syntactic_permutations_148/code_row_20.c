#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char message[256];
} UserMessage;

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulated database insertion logic.
    printf("Inserting into DB: %s: %s\n", username, message);
    return 1; // Success
}

void post(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message)) {
        printf("Redirecting to main page...\n");
    }
}

void display_messages(UserMessage messages[], int count) {
    for (int i = 0; i < count; ++i) {
        printf("%s: %s\n", messages[i].username, messages[i].message);
    }
}

int main() {
    UserMessage messages[3] = {
        {"Alice", "Hello, World!"},
        {"Bob", "Hi there!"},
        {"Charlie", "How are you?"}
    };

    display_messages(messages, 3);

    const char *username = "Dave";
    const char *message = "This is a new message!";
    
    post(username, message);
    return 0;
}