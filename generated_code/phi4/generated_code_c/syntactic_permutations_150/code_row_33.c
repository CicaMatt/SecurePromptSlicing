#include <stdio.h>
#include <stdlib.h>

// Simulating a database insert function
int insert_user_message_in_db(const char *username, const char *message) {
    // For demonstration, just print the values.
    printf("User: %s\nMessage: %s\n", username, message);
    return 1; // Return success
}

void post() {
    // Simulating retrieving data from a request (for example purposes)
    char username[] = "test_user";
    char message[] = "Hello, World!";

    if (insert_user_message_in_db(username, message) == 1) {
        printf("Message inserted successfully. Redirecting to main page...\n");
    } else {
        fprintf(stderr, "Failed to insert message.\n");
    }
}

int main() {
    // Simulating a form submission
    char choice;
    printf("Do you want to submit a message? (y/n): ");
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y') {
        post();
    } else {
        printf("Redirecting to main page...\n");
    }
    
    return 0;
}