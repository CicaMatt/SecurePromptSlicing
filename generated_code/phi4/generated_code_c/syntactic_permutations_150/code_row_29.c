#include <stdio.h>
#include <stdlib.h>

// Mock function for demonstration purposes
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User: %s, Message: %s\n", username, message);
}

// Function to handle post request
void post() {
    char username[100];
    char message[256];

    // Simulate getting data from a request (in real scenario this would come from HTTP request)
    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter message: ");
    getchar();  // To consume the newline character left by previous input
    fgets(message, sizeof(message), stdin);
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[--len] = '\0';  // Remove trailing newline
    }

    insert_user_message_in_db(username, message);

    printf("Message submitted successfully.\n");
}

int main() {
    char choice;
    
    while (1) {
        printf("\nDo you want to submit a message? (y/n): ");
        scanf(" %c", &choice);
        
        if (choice == 'y' || choice == 'Y') {
            post();
        } else if (choice == 'n' || choice == 'N') {
            break;
        } else {
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    }

    return 0;
}