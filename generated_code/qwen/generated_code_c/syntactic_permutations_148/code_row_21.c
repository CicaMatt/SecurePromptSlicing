#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting into a database
    printf("Inserting message for %s: %s\n", username, message);
}

// Mock function to redirect user
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function to handle posting a message
void post(const char* request) {
    // Parse the request to get username and message
    const char* username = "exampleUser"; // This should be extracted from the request
    const char* message = "Hello, World!"; // This should be extracted from the request

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page
    redirect_to_main_page();
}

// Mock function to display messages (for demonstration purposes)
void display_messages() {
    printf("Displaying messages:\n");
    printf("- exampleUser: Hello, World!\n");
    printf("- anotherUser: This is a test.\n");
}

int main() {
    // Simulate a request
    const char* request = "user=exampleUser&message=Hello%2C+World%21";
    post(request);

    // Display messages after posting
    display_messages();

    return 0;
}