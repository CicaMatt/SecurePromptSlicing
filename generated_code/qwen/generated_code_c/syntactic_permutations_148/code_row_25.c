#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insertion function
void insert_user_message_in_db(const char* username, const char* message) {
    // Here you would have your database insertion logic
    printf("Message from %s: %s inserted into the database.\n", username, message);
}

// Mock function to simulate getting data from a request
void get_request_data(const char** username, const char** message) {
    *username = "exampleUser";
    *message = "Hello, this is a test message!";
}

// Function to simulate redirecting the user
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function to display messages
void display_messages() {
    // Here you would retrieve messages from your database and print them
    printf("Displaying messages:\n");
    printf("Message 1: Hello from User1\n");
    printf("Message 2: Another message from User2\n");
}

// post function as described
void post() {
    const char* username;
    const char* message;

    get_request_data(&username, &message);
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    printf("User submits a message:\n");
    post();

    printf("\nDisplaying all messages:\n");
    display_messages();

    return 0;
}