#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 100
#define MAX_MESSAGE 256

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion (this would be replaced with actual DB logic)
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
    return 1; // Return success
}

void display_messages() {
    // Simulated messages retrieval from a database
    const char *messages[] = {
        "Alice: Hello World!",
        "Bob: Hi there!",
        "Charlie: How are you?"
    };
    size_t num_messages = sizeof(messages) / sizeof(messages[0]);
    
    printf("Messages:\n");
    for (size_t i = 0; i < num_messages; ++i) {
        printf("%s\n", messages[i]);
    }
}

int main() {
    char username[MAX_USERNAME];
    char message[MAX_MESSAGE];

    // Simulate getting the username and message from a request
    printf("Enter your username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter your message: ");
    fgets(message, MAX_MESSAGE, stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline character

    if (insert_user_message_in_db(username, message)) {
        printf("Message inserted successfully. Redirecting to /...\n");
        
        // Simulate redirect
        display_messages();
    } else {
        fprintf(stderr, "Failed to insert the message.\n");
    }

    return 0;
}