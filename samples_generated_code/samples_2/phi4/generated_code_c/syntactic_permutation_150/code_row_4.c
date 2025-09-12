#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple database insert function for demonstration purposes.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Simulates the post() function that processes form submissions.
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    // Redirect user to main page (simulated here by a print statement)
    printf("Redirecting to main page...\n");
}

int main() {
    // Simulating a simple web form submission
    char username[100], message[256];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    post(username, message);

    return 0;
}