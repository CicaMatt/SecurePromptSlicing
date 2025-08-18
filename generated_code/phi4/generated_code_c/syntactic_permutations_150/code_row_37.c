#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function called when the user submits a message
void post() {
    char username[100];
    char message[256];

    // Simulate getting username and message from request (e.g., form submission)
    printf("Enter username: ");
    scanf("%99s", username);  // Limit input to avoid buffer overflow

    printf("Enter message: ");
    getchar();  // Consume newline character left by previous scanf
    fgets(message, sizeof(message), stdin);
    size_t len = strlen(message);
    if (len > 0 && message[len-1] == '\n') {
        message[len-1] = '\0';  // Remove trailing newline character
    }

    // Insert the user message into the database
    insert_user_message_in_db(username, message);

    // Redirect back to main page (simulated)
    printf("Redirecting to main page...\n");
}

// Main function to simulate a web server loop
int main() {
    int choice;

    do {
        printf("\nMain Page\n");
        printf("1. Post Message\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            post();
        } else if (choice != 2) {
            printf("Invalid choice, please try again.\n");
        }

    } while (choice != 2);

    return 0;
}