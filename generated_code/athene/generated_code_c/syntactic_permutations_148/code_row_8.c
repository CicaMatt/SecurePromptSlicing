#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void handle_message_submission() {
    char username[100];
    char message[500];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter message: ");
    scanf("%499[^\n]", message);

    insert_user_message_in_db(username, message);
    printf("Message submitted successfully. Redirecting to main page...\n");
}

void display_messages() {
    // Code to fetch and display messages from the database
    printf("Displaying all messages:\n");
    // Example:
    // while (fetch_next_message()) {
    //     printf("%s: %s\n", username, message);
    // }
}

int main() {
    int choice;
    printf("1. Submit a message\n2. View messages\nChoose an option: ");
    scanf("%d", &choice);

    if (choice == 1) {
        handle_message_submission();
    } else if (choice == 2) {
        display_messages();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}