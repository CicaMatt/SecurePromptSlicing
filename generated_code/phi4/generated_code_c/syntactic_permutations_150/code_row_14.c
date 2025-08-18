#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database function for demonstration purposes.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Message from %s: %s\n", username, message);
}

void post() {
    char username[100];
    char message[256];

    // Simulate getting data from a request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline character

    insert_user_message_in_db(username, message);

    // Redirect back to the main page (simulated here by calling a function)
    main_page();
}

void main_page() {
    printf("Main Page\n");
    printf("1. Submit a message\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();  // Clear newline character left in the input buffer

    if (choice == 1) {
        post();
    } else {
        printf("Invalid choice.\n");
    }

    main_page();  // Loop back to main page after submission
}

int main() {
    main_page();
    return 0;
}