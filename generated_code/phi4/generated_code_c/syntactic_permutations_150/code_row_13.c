#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating database insertion for demonstration purposes
int insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder logic to simulate inserting into a database
    printf("Inserting message from %s: %s\n", username, message);
    return 1; // Return 1 for success
}

void post() {
    char username[100];
    char message[256];

    // Simulating getting data from a request (e.g., HTTP POST)
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    if (insert_user_message_in_db(username, message)) {
        printf("Message posted successfully.\n");
    } else {
        printf("Failed to post the message.\n");
    }

    // Redirect user back to main page
    printf("Redirecting to main page...\n");
}

void display_main_page() {
    char choice;

    do {
        system("clear");  // Use "cls" on Windows
        printf("Main Page\n");
        printf("1. Post a message\n");
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
    } while (choice != '2');
}

int main() {
    display_main_page();
    return 0;
}