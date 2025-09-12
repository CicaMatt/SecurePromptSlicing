#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

void post() {
    char username[50];
    char message[200];

    // Simulate getting data from a request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline character

    insert_user_message_in_db(username, message);

    // Simulate redirection
    printf("\nRedirecting user back to the form...\n");
}

void display_form() {
    printf("Please submit your message:\n\n");
    post();
}

int main() {
    while (1) {
        display_form();

        char choice;
        printf("\nDo you want to submit another message? (y/n): ");
        scanf("%c", &choice);
        getchar();  // Consume newline character

        if (choice == 'n' || choice == 'N') {
            break;
        }
    }

    return 0;
}