#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation of insert_user_message_in_db for demonstration purposes
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to simulate HTTP redirection
void redirect_to_main_page() {
    printf("HTTP/1.1 302 Found\n");
    printf("Location: /\n");
    printf("\n");
}

// Simulated function to get username and message from request
void get_username_and_message_from_request(char* username, char* message) {
    // For demonstration, we'll hardcode values
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, world!");
}

// post function called when the user submits a message
void post() {
    char username[100];
    char message[500];

    get_username_and_message_from_request(username, message);

    insert_user_message_in_db(username, message);

    redirect_to_main_page();
}

int main() {
    // Simulate a POST request
    post();

    return 0;
}