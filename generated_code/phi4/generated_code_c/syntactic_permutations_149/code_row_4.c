#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char message[256];
} UserMessage;

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion with a print statement
    printf("Inserting into DB: %s says '%s'\n", username, message);
}

void display_messages() {
    // Simulated data retrieval from the database
    UserMessage messages[] = {
        {"alice", "Hello World!"},
        {"bob", "Hi everyone!"},
        {"charlie", "Good morning!"}
    };
    
    int num_messages = sizeof(messages) / sizeof(messages[0]);
    
    printf("Messages:\n");
    for (int i = 0; i < num_messages; ++i) {
        printf("%s: %s\n", messages[i].username, messages[i].message);
    }
}

void redirect_to_home() {
    // Simulate a redirection
    printf("Redirecting to /...\n");
}

int main(void) {
    char username[50];
    char message[256];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    insert_user_message_in_db(username, message);

    display_messages();

    redirect_to_home();

    return 0;
}