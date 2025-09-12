#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting message into DB for user: %s\nMessage: %s\n", username, message);
}

// Function to redirect the user back to the main page
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function called when the user submits a message
void post(const char *username, const char *message) {
    if (username == NULL || message == NULL) {
        printf("Invalid input\n");
        return;
    }
    
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Example usage of the post function
    const char *username = "exampleUser";
    const char *message = "Hello, this is a test message!";
    
    post(username, message);
    
    return 0;
}