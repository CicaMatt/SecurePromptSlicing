#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming these are placeholder functions for demonstration purposes.
void insert_user_message_in_db(const char *username, const char *message) {
    // Logic to insert message into database
    printf("Inserting message from %s: %s into the database.\n", username, message);
}

void redirect_to_main_page() {
    // Placeholder logic for redirection
    printf("Redirecting to main page...\n");
}

// Function that will be called when user submits a message
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Simulating form submission by calling the post function directly.
    const char *username = "user123";
    const char *message = "Hello, this is a test message!";
    
    printf("User submitted a message.\n");
    post(username, message);
    
    return 0;
}