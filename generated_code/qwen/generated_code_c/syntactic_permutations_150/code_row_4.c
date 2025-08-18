#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database insertion function
void insert_user_message_in_db(const char* username, const char* message) {
    // This function would contain code to insert the message into a database
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to simulate form submission and redirection
void post() {
    // Simulated request data
    const char* username = "exampleUser";
    const char* message = "Hello, world!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("Redirecting to main page...\n");
}

// Simulated main function to demonstrate form submission
int main() {
    printf("Main Page\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");

    // Simulate form submission
    post();

    return 0;
}