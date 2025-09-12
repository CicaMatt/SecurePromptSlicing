#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void insert_user_message_in_db(const char* username, const char* message);
void redirect_to_main_page();

// Simulate the post function for demonstration purposes
void post() {
    char username[100];
    char message[256];

    // Simulating user input retrieval from request (e.g., web form)
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline character

    // Insert the user message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page
    redirect_to_main_page();
}

// Simulated function for inserting a user message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting message by %s: %s\n", username, message);
    // Database insertion logic would go here
}

// Simulate redirection to main page
void redirect_to_main_page() {
    printf("\nRedirecting back to the main page...\n");
    // Redirection logic would go here
}

int main() {
    // Main page with a form (simulated via console input)
    char option;
    
    do {
        printf("Main Page - Post Message\n");
        printf("1. Submit a message\n");
        printf("0. Exit\n");

        scanf("%c", &option);
        while(getchar() != '\n'); // Clear the newline character from buffer

        switch(option) {
            case '1':
                post();
                break;
            case '0':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (option != '0');

    return 0;
}