#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database.
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message from %s: %s\n", username, message);
    return 1; // Return success
}

void post() {
    char username[50];
    char message[256];

    // Simulating getting data from a request (e.g., form submission)
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline

    if (insert_user_message_in_db(username, message)) {
        printf("Message submitted successfully!\n");
        // Simulate redirecting to the main page
        system("echo Redirecting to main page...");
    } else {
        printf("Failed to submit message.\n");
    }
}

void display_main_page() {
    printf("\nMain Page\n");
    printf("Please enter your details below:\n");

    char action[10];
    do {
        printf("1. Submit a message\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        fgets(action, sizeof(action), stdin);
        action[strcspn(action, "\n")] = '\0'; // Remove newline

        if (strcmp(action, "1") == 0) {
            post();
        } else if (strcmp(action, "2") != 0) {
            printf("Invalid option. Please try again.\n");
        }
    } while (strcmp(action, "2") != 0);
}

int main() {
    display_main_page();
    return 0;
}