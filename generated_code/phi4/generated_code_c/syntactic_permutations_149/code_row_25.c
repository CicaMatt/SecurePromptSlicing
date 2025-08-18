#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insertion function
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    printf("Inserting into DB: Username=%s, Message=%s\n", username, message);
}

// Function to handle the /post route
void handle_post_route(char *username, char *message) {
    insert_user_message_in_db(username, message);
    printf("Redirecting to /route...\n");
}

int main() {
    // Simulate receiving a request with username and message
    char *username = "john_doe";
    char *message = "Hello, World!";

    handle_post_route(username, message);

    return 0;
}