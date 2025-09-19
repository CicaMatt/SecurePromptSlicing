#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void post() {
    char username[50];
    char message[256];

    // Simulating retrieval of data from request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    insert_user_message_in_db(username, message);

    // Simulating redirection to the main page
    printf("\nRedirecting to main page...\n");
}

void display_main_page() {
    printf("Main Page\n");
    printf("Please submit your message:\n");

    // Display form-like input prompt
    char choice;
    do {
        post();
        printf("Do you want to submit another message? (y/n): ");
        scanf("%c", &choice);
        getchar(); // Consume newline character left in the buffer

    } while (choice == 'y' || choice == 'Y');
}

int main() {
    display_main_page();
    return 0;
}