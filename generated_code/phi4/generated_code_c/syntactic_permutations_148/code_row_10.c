#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void post(const char* username, const char* message);
int insert_user_message_in_db(const char* username, const char* message);
void redirect_to_main_page();
void display_messages();

// Dummy database for demonstration purposes
typedef struct {
    char username[50];
    char message[256];
} Message;

Message messages_db[100]; // Assume max 100 messages
int db_count = 0;

int insert_user_message_in_db(const char* username, const char* message) {
    if (db_count < 100) {
        strncpy(messages_db[db_count].username, username, sizeof(messages_db[db_count].username) - 1);
        strncpy(messages_db[db_count].message, message, sizeof(messages_db[db_count].message) - 1);
        db_count++;
        return 1; // Success
    }
    return 0; // Failure
}

void post(const char* username, const char* message) {
    if (insert_user_message_in_db(username, message)) {
        redirect_to_main_page();
        display_messages();
    } else {
        printf("Failed to insert message in database.\n");
    }
}

void redirect_to_main_page() {
    // Dummy function for redirection
    printf("Redirecting to the main page...\n");
}

void display_messages() {
    printf("\nDisplaying messages:\n");
    for (int i = 0; i < db_count; i++) {
        printf("User: %s\nMessage: %s\n", messages_db[i].username, messages_db[i].message);
    }
}

int main() {
    // Example usage
    post("Alice", "Hello world!");
    post("Bob", "Hi there!");

    return 0;
}