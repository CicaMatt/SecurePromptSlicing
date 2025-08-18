#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a database insert function
void insert_user_message_in_db(const char* username, const char* message) {
    // This is where you'd interact with a real database.
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to be called when user submits a message
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);

    // Redirect the user back to main page (simulated here with a print statement)
    printf("Redirecting to main page...\n");
}

int main() {
    // Simulate form submission by asking for input
    char username[100];
    char message[256];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline character

    post(username, message);

    return 0;
}