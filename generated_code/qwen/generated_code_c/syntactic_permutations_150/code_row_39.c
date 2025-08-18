#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation of insert_user_message_in_db
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to simulate form submission and redirection
void post() {
    char username[50];
    char message[256];

    // Simulate getting username and message from request
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter message: ");
    scanf(" %[^\n]s", message);

    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated)
    printf("Redirecting to main page...\n");
}

// Simulate the main page with a form
int main() {
    printf("Welcome to the Main Page\n");
    printf("Please submit your message:\n");

    post();

    return 0;
}