#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy definition for database insertion function
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: Username=%s, Message=%s\n", username, message);
    return 1; // Simulate successful insertion
}

void post() {
    char username[100];
    char message[256];

    // Simulating retrieval of data from a request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    if (insert_user_message_in_db(username, message)) {
        printf("Message submitted successfully.\n");
    } else {
        printf("Failed to insert message into database.\n");
    }

    // Redirecting back to the main page
    printf("\nRedirecting to main page...\n\n");
}

int main() {
    char choice;

    do {
        printf("Main Page:\n");
        printf("1. Submit a message\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        scanf("%c", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case '1':
                post();
                break;
            case '2':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '2');

    return 0;
}