#include <stdio.h>
#include <stdlib.h>

// Mock function for inserting message into a database.
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to simulate redirecting back to the main page.
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function to handle post request
void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Example usage
    const char* username = "user123";
    const char* message = "Hello, world!";
    
    post(username, message);

    return 0;
}