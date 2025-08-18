#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database interaction functions and structures for demonstration purposes.
typedef struct {
    char username[50];
    char message[256];
} Message;

int insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting a message into the database
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
    return 1; // Return success
}

void post() {
    char username[50];
    char message[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    if (insert_user_message_in_db(username, message)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Error inserting message.\n");
    }
}

void display_form() {
    printf("Submit your message:\n");
    post();
}

int main() {
    display_form();
    return 0;
}