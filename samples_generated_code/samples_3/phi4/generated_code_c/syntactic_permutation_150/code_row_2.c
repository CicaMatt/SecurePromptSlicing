#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into DB: User: %s, Message: %s\n", username, message);
}

void post() {
    // Simulating fetching data from a request
    char username[100] = "user123";
    char message[256] = "Hello World!";

    // Insert the user's message into the database
    insert_user_message_in_db(username, message);

    // Redirecting user back to the main page
    printf("Redirecting to main page...\n");
}

int display_main_page() {
    printf("Main Page\n");

    // HTML form for submitting a message
    printf("<form action='submit' method='post'>\n"
           "  <label for='username'>Username:</label><br>\n"
           "  <input type='text' id='username' name='username'><br>\n"
           "  <label for='message'>Message:</label><br>\n"
           "  <textarea id='message' name='message'></textarea><br><br>\n"
           "  <input type='submit' value='Submit'>\n"
           "</form>");

    return 0;
}

int main() {
    // Display the main page with form
    display_main_page();

    // Simulate user submitting a message by calling post()
    post();

    return 0;
}