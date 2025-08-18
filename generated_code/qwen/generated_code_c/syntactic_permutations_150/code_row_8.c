#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation of database insertion function
void insert_user_message_in_db(const char* username, const char* message) {
    // Database logic here
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

// Function to handle form submission
void post() {
    char username[50];
    char message[256];

    // Simulate getting username and message from a request
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    // Insert the user's message into the database
    insert_user_message_in_db(username, message);

    // Redirect back to the main page (simulated with a print statement)
    printf("Redirecting back to the main page.\n");
}

// Function to simulate displaying the main page with a form
void display_main_page() {
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Main Page</h1>\n");
    printf("<form method=\"post\" action=\"/post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <input type=\"text\" name=\"message\"><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate a form submission
    post();

    // Display the main page with a form
    display_main_page();

    return 0;
}