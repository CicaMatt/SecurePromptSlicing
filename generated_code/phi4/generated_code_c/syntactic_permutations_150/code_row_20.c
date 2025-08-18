#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting a message into the database.
void insert_user_message_in_db(const char *message) {
    // Simulate database insertion logic here.
    printf("Message inserted into database: %s\n", message);
}

// Function to redirect user back to main page (mock).
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Post function called when the user submits a message
void post(const char *message) {
    insert_user_message_in_db(message);
    redirect_to_main_page();
}

int main(void) {
    // Simulate form submission with a static message.
    const char *user_message = "Hello, this is a test message!";
    
    printf("User submitted a message.\n");
    post(user_message);

    return 0;
}