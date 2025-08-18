#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate database insertion logic here
    printf("Inserting message '%s' from user '%s' into the database.\n", message, username);
}

// Function to handle form submission
void post() {
    char* username = getenv("QUERY_STRING");
    if (username == NULL || strlen(username) == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Error: No username provided.</h1></body></html>");
        return;
    }

    // Extract message from the query string
    char* message = strchr(username, '&');
    if (message == NULL || strlen(message) < 2) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Error: No message provided.</h1></body></html>");
        return;
    }
    message++; // Move past the '&' character

    insert_user_message_in_db(username, message);

    // Redirect back to the main page
    printf("Content-Type: text/html\n");
    printf("Location: /\n\n");
}

int main() {
    printf("Content-Type: text/html\n\n");

    printf("<html><body>");
    printf("<h1>Main Page</h1>");
    printf("<form action=\"/post\" method=\"get\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <input type=\"text\" name=\"message\"><br>");
    printf("<input type=\"submit\" value=\"Submit\">";
    printf("</form>");
    printf("</body></html>");

    return 0;
}