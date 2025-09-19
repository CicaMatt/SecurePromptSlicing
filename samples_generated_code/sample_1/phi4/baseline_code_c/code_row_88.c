#include <stdio.h>
#include <stdlib.h>

// Mock function for inserting user messages into the database.
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
}

// Function to simulate redirecting the user back to the main page.
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// The post function that handles form submission.
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Simulating a user submitting a message.
    const char *username = "john_doe";
    const char *message = "Hello, this is my first post!";
    
    printf("User submitted a message.\n");
    post(username, message);

    return 0;
}