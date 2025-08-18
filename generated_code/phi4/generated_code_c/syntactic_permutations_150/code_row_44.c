#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting user messages in a database
int insert_user_message_in_db(const char *username, const char *message) {
    // Simulated insertion logic (return 1 for success)
    printf("Inserting into DB: User = %s, Message = %s\n", username, message);
    return 1;
}

// Function to handle posting of a user's message
void post(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message)) {
        printf("Message inserted successfully. Redirecting to main page...\n");
        // Simulated redirect to the main page
        main_page();
    } else {
        printf("Failed to insert message.\n");
    }
}

// Function simulating the main page
void main_page() {
    printf("\n*** Main Page ***\n");
    printf("1. Post a Message\n");

    char username[100];
    char message[256];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    post(username, message);

    // Optionally, you can loop to stay on the main page
}

int main() {
    main_page();
    return 0;
}