#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulated database insertion logic
    printf("Inserting message '%s' for user '%s' into the database.\n", message, username);
}

// Function to handle POST request
void post() {
    char *username = getenv("HTTP_POST_USERNAME");
    char *message = getenv("HTTP_POST_MESSAGE");

    if (username && message) {
        insert_user_message_in_db(username, message);
    }

    // Redirect back to the main page
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=/main.html\"></head></html>");
}

// Main function to simulate server handling a request
int main() {
    // Simulating a POST request with environment variables
    setenv("HTTP_POST_USERNAME", "exampleUser", 1);
    setenv("HTTP_POST_MESSAGE", "Hello, World!", 1);

    post();

    return 0;
}