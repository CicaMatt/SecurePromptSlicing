#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into the database
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to simulate handling a POST request
void post() {
    // Simulated input from a web form
    char username[50] = "exampleUser";
    char message[256] = "Hello, this is a test message!";

    insert_user_message_in_db(username, message);

    // Redirect to the main page (simulated with a printf)
    printf("Redirecting back to the main page...\n");
}

int main() {
    // Simulate form submission
    post();

    return 0;
}