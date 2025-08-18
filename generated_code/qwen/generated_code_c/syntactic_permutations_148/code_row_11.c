#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate database insertion logic here
    printf("Message from %s: %s inserted into the database.\n", username, message);
}

// Mock function to simulate getting request data (in a real scenario this would parse HTTP requests)
void get_request_data(const char** username, const char** message) {
    *username = "exampleUser";
    *message = "Hello, World!";
}

// Function to handle posting a new message
void post() {
    const char* username;
    const char* message;

    // Get the username and message from the request
    get_request_data(&username, &message);

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user to the main page (simulated with a print statement)
    printf("Redirecting to main page...\n");
}

// Mock function to simulate fetching messages from a database
void fetch_messages_from_db(char*** messages, int* count) {
    *count = 3;
    *messages = malloc(*count * sizeof(char*));
    (*messages)[0] = strdup("User1: First message.");
    (*messages)[1] = strdup("User2: Second message.");
    (*messages)[2] = strdup("User1: Another message.");
}

// Function to display messages
void display_messages() {
    char** messages;
    int count;

    // Fetch messages from the database
    fetch_messages_from_db(&messages, &count);

    // Display each message
    for (int i = 0; i < count; i++) {
        printf("%s\n", messages[i]);
        free(messages[i]); // Free allocated memory for each message
    }

    // Free the array of message pointers
    free(messages);
}

int main() {
    post();
    display_messages();
    return 0;
}