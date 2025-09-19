#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting message into a database
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
    return 1; // Success
}

void post() {
    char username[100];
    char message[256];

    // Simulating getting data from request (normally done with actual HTTP handling)
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    if (insert_user_message_in_db(username, message)) {
        printf("Message inserted successfully.\n");
    } else {
        printf("Failed to insert message.\n");
    }

    // Redirect user back to main page
    printf("Redirecting to main page...\n");
}

void display_form() {
    printf("\n--- Main Page ---\n");
    printf("Please submit your message:\n\n");

    // Simulate HTML form input in console application
    post();
}

int main() {
    while (1) {
        display_form();

        char choice;
        printf("Do you want to submit another message? (y/n): ");
        scanf("%c", &choice);
        getchar(); // consume newline character

        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }

    return 0;
}