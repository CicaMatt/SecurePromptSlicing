#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

// Function to handle the post request
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    // Redirect back to main page (simulated with a print)
    printf("Redirecting back to main page...\n");
}

int main() {
    // Simulated form submission
    char username[100];
    char message[256];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    post(username, message);

    return 0;
}