#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a user message into a database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserting message for %s: %s\n", username, message);
}

// Function to handle the post request
void post() {
    // For demonstration purposes, we'll use fixed values for username and message
    // In a real application, these would be retrieved from the request
    const char *username = "user123";
    const char *message = "Hello, world!";

    // Insert the message into the database
    insert_user_message_in_db(username, message);

    // Redirect the user back to the main page
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: /\r\n");
    printf("\r\n");
}

// Mock function to simulate displaying the main page with a form
void display_main_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>\n");
    printf("<h1>Main Page</h1>\n");
    printf("<form method=\"post\" action=\"/post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

int main() {
    // For demonstration, we'll assume the request method is POST
    // In a real application, this would be determined by the server
    post();
    display_main_page();

    return 0;
}