#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting user message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion logic here
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle the POST request
void post() {
    char username[100];
    char message[500];

    // Simulate getting username and message from a request
    printf("Enter your username: ");
    scanf("%99s", username);
    printf("Enter your message: ");
    getchar(); // To consume the newline character left in the buffer after reading the username
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character if present

    // Insert the user message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page (simulated with a print statement)
    printf("User redirected back to the main page.\n");
}

int main() {
    // Simulate form submission by calling the post function
    post();
    return 0;
}