#include <stdio.h>
#include <stdlib.h>

// Mock function for inserting user message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Function to handle post request and redirect back to main page
void post() {
    char username[100];
    char message[256];

    // Simulate getting username and message from user input
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline character

    insert_user_message_in_db(username, message);

    // Simulate redirecting to main page
    printf("Redirecting to the main page...\n");
}

// Function to display the form and handle user input
void display_form() {
    printf("Message Form:\n");
    post();
}

int main() {
    display_form();
    return 0;
}