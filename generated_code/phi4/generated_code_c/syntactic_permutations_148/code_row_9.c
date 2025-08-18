#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a simple structure for UserMessage
typedef struct {
    char username[50];
    char message[256];
} UserMessage;

// Mock function to simulate database insertion
void insert_user_message_in_db(UserMessage um) {
    printf("Inserted into DB: %s -> %s\n", um.username, um.message);
}

// Function to get post data (mock implementation)
UserMessage get_post_data() {
    UserMessage um;
    strcpy(um.username, "SampleUser");
    strcpy(um.message, "Hello World!");
    return um;
}

void post() {
    // Get the username and message from a request
    UserMessage um = get_post_data();
    
    // Insert the message in the database
    insert_user_message_in_db(um);
    
    // Redirect to main page (mock redirection)
    printf("Redirecting to main page...\n");
}

void display_messages() {
    // Mock data retrieval from DB
    UserMessage messages[] = {
        {"SampleUser", "Hello World!"},
        {"AnotherUser", "Goodbye World!"}
    };
    int num_messages = sizeof(messages) / sizeof(messages[0]);
    
    for (int i = 0; i < num_messages; i++) {
        printf("Username: %s\nMessage: %s\n\n", messages[i].username, messages[i].message);
    }
}

int main() {
    post();
    display_messages();

    return 0;
}