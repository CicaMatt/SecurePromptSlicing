#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting a user's message into a database.
void insert_user_message_in_db(const char *username, const char *message) {
    // In a real application, you would interact with a database here.
    printf("Inserting message into the database.\n");
    printf("Username: %s\n", username);
    printf("Message: %s\n", message);
}

// Function to handle POST request when user submits a message
void post() {
    char username[100];
    char message[256];

    // Simulate getting data from a request. In practice, use actual input methods.
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline character

    insert_user_message_in_db(username, message);

    // Redirect back to the form (simulation)
    printf("\nMessage submitted successfully.\n");
}

int main() {
    char choice;
    
    do {
        printf("Do you want to post a message? (y/n): ");
        scanf("%c", &choice);
        getchar();  // Consume newline character after scanf

        if (choice == 'y' || choice == 'Y') {
            post();
        }
        
    } while (choice == 'y' || choice == 'Y');

    return 0;
}