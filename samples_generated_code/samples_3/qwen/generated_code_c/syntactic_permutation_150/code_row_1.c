#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting user message into database
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate database insertion
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

// Function to handle the POST request
void post() {
    char username[50];
    char message[256];

    // Assume these values are obtained from the HTTP request
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    insert_user_message_in_db(username, message);

    // Redirect to main page
    printf("HTTP/1.1 302 Found\nLocation: /\n\n");
}

int main() {
    // Simulate a POST request
    post();

    // HTML for the main page with a form to submit a message
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h1>Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body></html>");

    return 0;
}