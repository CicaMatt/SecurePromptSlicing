#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion.
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into DB: User: %s, Message: %s\n", username, message);
}

// Function to get the username and message from a simulated request
// and call insert_user_message_in_db() function.
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    // Redirecting user back to main page (simulation)
    printf("Redirecting to main page...\n");
}

// Function to display the form for submitting messages
void display_form() {
    printf("Form to submit a message:\n");
    printf("<form action='/submit' method='post'>\n");
    printf("  <label>Username:</label>\n");
    printf("  <input type='text' name='username'/><br/>\n");
    printf("  <label>Message:</label>\n");
    printf("  <textarea name='message'></textarea><br/>\n");
    printf("  <button type='submit'>Submit</button>\n");
    printf("</form>\n");
}

// Main function to simulate the process
int main() {
    // Display form for user input
    display_form();

    // Simulate user input and post request
    const char *username = "test_user";
    const char *message = "Hello, this is a test message.";

    // Call the post function with simulated data
    post(username, message);

    return 0;
}