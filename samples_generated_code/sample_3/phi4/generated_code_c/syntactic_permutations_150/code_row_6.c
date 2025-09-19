#include <stdio.h>
#include <string.h>

// Mockup for database insertion function
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message into DB...\n");
    printf("Username: %s\nMessage: %s\n", username, message);
    // Simulate successful insertion
    return 1;
}

// Function to handle the post request
void post() {
    char username[100];
    char message[256];

    // Mockup for getting data from a request (usually comes from HTTP request)
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    username[strcspn(username, "\n")] = 0;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    // Remove newline character if present
    message[strcspn(message, "\n")] = 0;

    if (insert_user_message_in_db(username, message)) {
        printf("Message submitted successfully.\n");
    } else {
        printf("Failed to submit the message.\n");
    }
}

int main() {
    // Simulate a form submission by calling the post function
    post();

    return 0;
}