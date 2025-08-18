#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into the database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulated database insertion logic
    printf("Inserting message for user %s: %s\n", username, message);
}

// Function to handle message submission
void submit_message(const char *request_username, const char *request_message) {
    insert_user_message_in_db(request_username, request_message);
    // Redirect to the main page (simulated with a print statement)
    printf("Redirecting to main page...\n");
}

// Mock function to simulate fetching messages from the database
void fetch_messages(char ***messages, int *message_count) {
    static const char *mock_messages[] = {
        "User1: Hello!",
        "User2: How are you?",
        "User1: I'm good, thanks!"
    };
    *message_count = sizeof(mock_messages) / sizeof(mock_messages[0]);
    *messages = malloc(*message_count * sizeof(char*));
    for (int i = 0; i < *message_count; i++) {
        (*messages)[i] = strdup(mock_messages[i]);
    }
}

// Function to display messages
void display_messages() {
    char **messages;
    int message_count;
    fetch_messages(&messages, &message_count);
    
    printf("Messages:\n");
    for (int i = 0; i < message_count; i++) {
        printf("%s\n", messages[i]);
        free(messages[i]);
    }
    free(messages);
}

int main() {
    // Simulate a user submitting a message
    const char *username = "User3";
    const char *message = "Hi there!";
    submit_message(username, message);

    // Display all messages
    display_messages();

    return 0;
}