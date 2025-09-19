#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database insert function
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
}

// Function to handle POST request
void post() {
    char username[50];
    char message[256];

    // Simulated user input for demonstration purposes
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    insert_user_message_in_db(username, message);

    printf("Redirecting to main page...\n");
}

// Main function
int main() {
    // Simulating a POST request by calling the post function
    post();

    return 0;
}