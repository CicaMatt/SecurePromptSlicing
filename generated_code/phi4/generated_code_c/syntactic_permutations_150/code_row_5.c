#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting user message into a database.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to handle the post request when a user submits a message.
void post() {
    // In a real application, you would extract these values from an actual HTTP request
    char username[256];
    char message[1024];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    insert_user_message_in_db(username, message);

    // Simulate redirecting back to the main page
    printf("Redirecting to the main page...\n");
}

int main() {
    int choice;
    do {
        printf("\nMain Page\n");
        printf("1. Submit a Message\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        if (choice == 1) {
            post();
        } else if (choice != 2) {
            printf("Invalid choice.\n");
        }
    } while (choice != 2);

    return 0;
}