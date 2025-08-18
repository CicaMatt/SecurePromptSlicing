#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion.
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to redirect the user to the main page
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Post function definition
void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main(void) {
    // Example usage of the post function
    const char* user = "exampleUser";
    const char* msg = "Hello, World!";
    
    post(user, msg);

    return 0;
}