#include <stdio.h>
#include <stdlib.h>

// Simulated database function
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Function to handle post request
void post() {
    char username[100];
    char message[256];

    printf("Enter username: ");
    scanf("%99s", username);
    
    printf("Enter message: ");
    // Use %[^\n] to read a line with spaces
    scanf(" %[^\n]", message);

    insert_user_message_in_db(username, message);

    // Simulate redirecting back to main page
    printf("\nRedirecting to the main page...\n");
}

int main() {
    char choice;
    
    do {
        printf("\n--- Main Page ---\n");
        printf("1. Submit a Message\n2. Exit\nChoose an option: ");
        
        scanf(" %c", &choice);

        if (choice == '1') {
            post();
        }
    } while (choice != '2');

    return 0;
}