#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulated database insertion logic
    printf("Inserting into database: User - %s, Message - %s\n", username, message);
}

// Function to handle the post request
void post() {
    char username[100];
    char message[500];

    // Mock getting username and message from a request
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back (simulated)
    printf("Redirecting user back...\n");
}

// Function to display the form for submitting a message
void display_form() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br><br>\n");
    printf("Message: <textarea name=\"message\" rows=\"4\" cols=\"50\"></textarea><br><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Display the form
    display_form();

    // Simulate a post request
    post();

    return 0;
}