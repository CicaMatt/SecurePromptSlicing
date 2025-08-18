#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion logic here
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle the post request
void post() {
    // For demonstration purposes, we'll use hardcoded values
    // In a real application, these would be retrieved from the request
    const char *username = "user123";
    const char *message = "Hello, this is a test message!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("Content-Type: text/html\n");
    printf("Location: /\n\n");
}

// Mock function to simulate displaying the main page with a form
void display_main_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Main Page</h1>");
    printf("<form action=\"/post\" method=\"post\">");
    printf("<label for=\"username\">Username:</label><br>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
    printf("<label for=\"message\">Message:</label><br>");
    printf("<textarea id=\"message\" name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    // Simulate a post request
    if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    } else {
        display_main_page();
    }
    return 0;
}