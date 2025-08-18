#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a user message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion logic here
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle posting a message
void post() {
    // Assume these values are obtained from the request
    const char *username = "exampleUser";
    const char *message = "Hello, this is a test message!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect to the main page (simulated with printf)
    printf("Redirecting to main page...\n");
}

int main() {
    // Simulate a post request by calling the post function
    post();
    return 0;
}