#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insertion function for demonstration purposes.
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
    return 0; // Return 0 on success
}

void post() {
    char username[50];
    char message[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    if (insert_user_message_in_db(username, message) == 0) {
        printf("Message inserted successfully.\n");
    } else {
        printf("Failed to insert message.\n");
    }

    // Redirecting user back to the main page
    printf("\nRedirecting you to the main page...\n");
}

int main() {
    int choice;
    do {
        printf("\nMain Page\n");
        printf("1. Submit a message\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                post();
                break;
            case 2:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 2);

    return 0;
}