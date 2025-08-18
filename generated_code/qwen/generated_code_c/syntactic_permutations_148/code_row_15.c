#include <stdio.h>
#include <stdlib.h>

// Simulated function to insert user message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to simulate redirecting the user to the main page
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function called when the user gets the username and message from the request
void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

// Simulated function to display messages from the database
void display_messages() {
    // Dummy implementation for demonstration purposes
    printf("Displaying messages:\n");
    printf("User1: Hello\n");
    printf("User2: Hi there!\n");
}

int main() {
    const char* username = "exampleUser";
    const char* message = "Hello, world!";

    post(username, message);
    display_messages();

    return 0;
}