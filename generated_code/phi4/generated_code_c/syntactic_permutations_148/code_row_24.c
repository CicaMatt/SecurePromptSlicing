#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_MESSAGE 256

typedef struct {
    char username[MAX_USERNAME];
    char message[MAX_MESSAGE];
} UserMessage;

void insert_user_message_in_db(const UserMessage *um) {
    // Simulate database insertion (e.g., print to console)
    printf("Inserting into DB: Username=%s, Message=%s\n", um->username, um->message);
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

void post(const char *username, const char *message) {
    UserMessage um;
    
    strncpy(um.username, username, MAX_USERNAME - 1);
    um.username[MAX_USERNAME - 1] = '\0';
    strncpy(um.message, message, MAX_MESSAGE - 1);
    um.message[MAX_MESSAGE - 1] = '\0';

    insert_user_message_in_db(&um);
    redirect_to_main_page();
}

void display_messages() {
    // Simulate fetching from database
    UserMessage messages[] = {
        {"Alice", "Hello World!"},
        {"Bob", "Hi there!"},
        {"Charlie", "How are you?"}
    };
    size_t num_messages = sizeof(messages) / sizeof(UserMessage);
    
    printf("Messages:\n");
    for (size_t i = 0; i < num_messages; ++i) {
        printf("%s: %s\n", messages[i].username, messages[i].message);
    }
}

int main() {
    // Simulate user input
    const char *username = "Dave";
    const char *message = "This is a test message.";

    post(username, message);

    display_messages();

    return 0;
}