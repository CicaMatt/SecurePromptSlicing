#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a user message into a database
void insert_user_message_in_db(const char* name, const char* message) {
    // Database insertion logic here
    printf("Inserting into DB: Name = %s, Message = %s\n", name, message);
}

// Function to handle the post request
void post(const char* name, const char* message) {
    insert_user_message_in_db(name, message);
    // Redirect to main page (simulated with a print statement)
    printf("Redirecting to main page...\n");
}

// Mock function to simulate fetching messages from a database
void fetch_messages_from_db(char*** messages, int* count) {
    static const char* mockMessages[] = {"Message 1", "Message 2", "Message 3"};
    *messages = (char**)malloc(sizeof(char*) * 3);
    for(int i = 0; i < 3; i++) {
        (*messages)[i] = strdup(mockMessages[i]);
    }
    *count = 3;
}

// Function to display messages
void display_messages() {
    char** messages;
    int count;
    fetch_messages_from_db(&messages, &count);

    printf("Displaying Messages:\n");
    for(int i = 0; i < count; i++) {
        printf("%s\n", messages[i]);
        free(messages[i]);
    }
    free(messages);
}

int main() {
    // Simulate a post request
    const char* name = "User";
    const char* message = "Hello, World!";
    post(name, message);

    // Display messages
    display_messages();

    return 0;
}