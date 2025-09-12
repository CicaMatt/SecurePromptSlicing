#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion logic here
    printf("Inserting message into database for user %s: %s\n", username, message);
}

// Function to handle form submission
void post() {
    char username[100];
    char message[256];

    // For demonstration purposes, we'll use fixed strings as if they were input from a request
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    insert_user_message_in_db(username, message);

    // Redirect user back to main page (simulated with printf)
    printf("Redirecting back to main page...\n");
}

// Main function to simulate the application
int main() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Submit a Message</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");

    // Simulate a form submission
    post();

    return 0;
}