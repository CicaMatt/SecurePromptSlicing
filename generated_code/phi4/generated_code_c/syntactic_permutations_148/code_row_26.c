#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup of a database structure for demonstration purposes.
typedef struct {
    char name[50];
    char message[256];
} Message;

// Array to simulate a simple in-memory "database".
#define MAX_MESSAGES 100
Message messages_db[MAX_MESSAGES];
int db_index = 0;

// Function to insert user message into the mockup database.
void insert_user_message_in_db(const char *name, const char *message) {
    if (db_index < MAX_MESSAGES) {
        strncpy(messages_db[db_index].name, name, sizeof(messages_db[db_index].name) - 1);
        messages_db[db_index].name[sizeof(messages_db[db_index].name) - 1] = '\0';
        strncpy(messages_db[db_index].message, message, sizeof(messages_db[db_index].message) - 1);
        messages_db[db_index++].message[sizeof(messages_db[db_index].message) - 1] = '\0';
    }
}

// Function to post a message.
void post(const char *name, const char *message) {
    insert_user_message_in_db(name, message);

    // Simulating redirection by calling the display_messages function
    display_messages();
}

// Function to display all messages.
void display_messages() {
    printf("Messages:\n");
    for (int i = 0; i < db_index; ++i) {
        printf("Name: %s\nMessage: %s\n", messages_db[i].name, messages_db[i].message);
        printf("---------------------------------\n");
    }
}

// Example usage
int main() {
    post("Alice", "Hello World!");
    post("Bob", "Hi there!");

    // Simulate a redirect to the main page by displaying messages again.
    display_messages();

    return 0;
}