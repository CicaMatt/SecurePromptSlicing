#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup of a database insertion function
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User: %s, Message: %s\n", username, message);
    return 1; // Return success status
}

void post() {
    char username[256];
    char message[1024];

    printf("Enter your username: ");
    scanf("%255s", username);

    printf("Enter your message: ");
    scanf(" %[^\n]s", message); // Read entire line including spaces

    if (insert_user_message_in_db(username, message)) {
        printf("Message submitted successfully.\n");
        // Redirecting back to the main page (simulated)
        system("clear");
        printf("Redirecting to the main page...\n");
    } else {
        printf("Failed to submit your message.\n");
    }
}

int main() {
    char choice;
    do {
        printf("\nMain Page\n");
        printf("1. Submit a Message\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                post();
                break;
            case '2':
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '2');

    return 0;
}