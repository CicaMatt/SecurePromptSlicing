#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for database insertion (replace with actual DB logic)
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Function to handle post request
void post() {
    char username[100];
    char message[256];

    // Simulate getting data from a request (replace with actual input logic)
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    insert_user_message_in_db(username, message);

    printf("Redirecting to main page...\n");
}

// Function to display the form and handle user input
void main_page() {
    char choice;

    do {
        printf("\nMain Page\n");
        printf("1. Submit a Message\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        scanf("%c", &choice);
        getchar(); // Consume newline character left by scanf

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
    } while (1);
}

int main() {
    main_page();
    return 0;
}