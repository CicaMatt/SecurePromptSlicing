#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting user message into a database
void insert_user_message_in_db(const char* username, const char* message) {
    // Database insertion logic here
    printf("Inserting message for %s: %s\n", username, message);
}

// Function called when the user submits a message
void post() {
    char* username = getenv("QUERY_STRING");
    if (username == NULL || strlen(username) == 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Error: No username provided.</body></html>");
        return;
    }

    // For simplicity, let's assume the message follows the username in the query string
    char* message = strchr(username, '&');
    if (message == NULL || strlen(message) < 2) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Error: No message provided.</body></html>");
        return;
    }
    message++; // Move past the '&' character

    insert_user_message_in_db(username, message);

    // Redirect back to the main page
    printf("Location: /\r\n\r\n");
}

int main() {
    // Check if this is a POST request (in practice, you'd check REQUEST_METHOD)
    const char* method = getenv("REQUEST_METHOD");
    if (method != NULL && strcmp(method, "POST") == 0) {
        post();
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<form action=\"/post\" method=\"post\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Message: <textarea name=\"message\"></textarea><br>");
        printf("<input type=\"submit\" value=\"Submit\">");
        printf("</form>");
        printf("</body></html>");
    }
    return 0;
}