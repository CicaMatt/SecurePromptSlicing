#include <stdio.h>
#include <stdlib.h>

// Mock database interaction functions

void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into a database
    printf("Inserting into DB: User = %s, Message = %s\n", username, message);
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function to handle the post request
void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Simulate user input
    const char* username = "user123";
    const char* message = "Hello, World!";
    
    // Call the post function as if it's being triggered by a form submission
    post(username, message);

    return 0;
}