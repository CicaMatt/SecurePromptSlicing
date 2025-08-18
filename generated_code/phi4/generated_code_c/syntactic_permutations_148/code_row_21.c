#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structure for request data
typedef struct {
    char username[50];
    char message[256];
} Request;

// Function prototypes
void insert_user_message_in_db(const char *username, const char *message);
void redirect_to_main_page();
void display_messages();

int main() {
    // Simulating user input
    Request req;
    strcpy(req.username, "user123");
    strcpy(req.message, "Hello World!");

    post(&req);

    return 0;
}

// Function to handle posting a message
void post(Request *request) {
    char username[50];
    char message[256];

    // Get username and message from request
    strncpy(username, request->username, sizeof(username));
    strncpy(message, request->message, sizeof(message));

    // Insert user message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page
    redirect_to_main_page();
}

// Mock function for inserting a message into the database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting %s's message: %s into database...\n", username, message);
    // Database insertion logic would go here
}

// Mock function to redirect user to main page
void redirect_to_main_page() {
    printf("\nRedirecting to the main page...\n");
    display_messages();
}

// Function to display messages (mock implementation)
void display_messages() {
    printf("Displaying all messages:\n");
    // In a real application, this would fetch and display messages from the database
    printf("user123: Hello World!\n");
}