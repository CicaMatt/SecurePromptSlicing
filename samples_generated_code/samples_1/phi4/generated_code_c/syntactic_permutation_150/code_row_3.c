#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to handle form submission (simulated)
void post(const char *username, const char *message) {
    // Insert the user's message into the database
    insert_user_message_in_db(username, message);

    // Redirect user back to the main page (simulation)
    printf("Redirecting to main page...\n");
}

int main() {
    // Simulate form submission by calling post()
    const char *username = "sampleUser";
    const char *message = "Hello, World!";

    post(username, message);

    return 0;
}