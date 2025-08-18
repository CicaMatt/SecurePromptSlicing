#include <stdio.h>
#include <stdlib.h>

// Mock function to simulate inserting a message in the database.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: Username=%s, Message=%s\n", username, message);
}

// Function to handle user post request
void post() {
    char username[100];
    char message[256];

    // Simulating getting data from a form submission.
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;  // Remove newline character

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;  // Remove newline character

    insert_user_message_in_db(username, message);

    // Redirecting user back to the main page (simulation)
    printf("\nRedirecting to main page...\n");
}

// Main function to display a simple form and call post()
int main() {
    char choice;

    do {
        printf("Welcome to the Message Board\n");
        printf("---------------------------\n");
        printf("1. Post a message\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        scanf("%c", &choice);
        getchar();  // Clear newline character from buffer

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