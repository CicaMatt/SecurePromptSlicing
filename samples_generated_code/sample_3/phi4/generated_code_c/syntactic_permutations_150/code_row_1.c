#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void post();
int insert_user_message_in_db(const char *username, const char *message);
void redirect_to_main_page();

// Simulated request structure for demonstration purposes
typedef struct {
    char username[100];
    char message[256];
} Request;

Request current_request = {"", ""};

// Dummy implementation of inserting a message into the database
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User: %s, Message: %s\n", username, message);
    return 1; // Return success
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Main function for testing purposes
int main() {
    // Simulate filling the request with user data
    strcpy(current_request.username, "testuser");
    strcpy(current_request.message, "Hello, World!");

    post();

    return 0;
}

void post() {
    const char *username = current_request.username;
    const char *message = current_request.message;

    if (insert_user_message_in_db(username, message)) {
        redirect_to_main_page();
    } else {
        printf("Failed to insert message.\n");
    }
}