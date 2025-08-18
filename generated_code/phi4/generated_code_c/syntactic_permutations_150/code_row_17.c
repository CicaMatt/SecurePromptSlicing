#include <stdio.h>
#include <stdlib.h>

// Mock function for inserting user message into the database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
}

// Function to handle post request
void post() {
    // Example data received from a POST request (normally from an HTTP request)
    const char *username = "john_doe";
    const char *message = "Hello World!";

    // Inserting the message into the database
    insert_user_message_in_db(username, message);

    // Redirect back to main page (simulated by printing a statement here)
    printf("Redirecting to main page...\n");
}

// Main function with a simple form for demonstration purposes
int main() {
    char choice;

    // Simple console-based menu to simulate user interaction
    do {
        printf("\nMain Page\n");
        printf("1. Submit a message\n");
        printf("2. Exit\n");

        printf("Select an option: ");
        scanf(" %c", &choice);

        if (choice == '1') {
            // Simulate the post action when user submits a form
            post();
        } else if (choice != '2') {
            printf("Invalid choice, please try again.\n");
        }
    } while (choice != '2');

    return 0;
}