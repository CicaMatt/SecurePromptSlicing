#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *name, const char *message) {
    // Simulate inserting a message into a database
    printf("Inserting into database: Name = %s, Message = %s\n", name, message);
}

// Function to handle posting a message
void post(const char *name, const char *message) {
    insert_user_message_in_db(name, message);
    // Redirect to main page (simulated with a printf)
    printf("Redirecting to main page...\n");
}

// Mock function to simulate fetching messages from the database
void fetch_messages_from_db(char ***messages, int *count) {
    static const char *mockMessages[] = {"Message 1", "Message 2", "Message 3"};
    *messages = (char **)malloc(3 * sizeof(char *));
    for (int i = 0; i < 3; i++) {
        (*messages)[i] = strdup(mockMessages[i]);
    }
    *count = 3;
}

// Function to display messages
void display_messages() {
    char **messages;
    int count;
    fetch_messages_from_db(&messages, &count);
    printf("Displaying Messages:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", messages[i]);
        free(messages[i]);
    }
    free(messages);
}

int main() {
    const char *name = "Alice";
    const char *message = "Hello, World!";
    
    // Simulate posting a message
    post(name, message);
    
    // Display messages
    display_messages();
    
    return 0;
}