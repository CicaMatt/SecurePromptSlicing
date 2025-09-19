#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to handle form submission
void post() {
    char *username = getenv("HTTP_POST_USERNAME");
    char *message = getenv("HTTP_POST_MESSAGE");

    if (username == NULL || message == NULL) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Error: Missing username or message</h1></body></html>");
        return;
    }

    insert_user_message_in_db(username, message);

    // Redirect back to the main page
    printf("Location: /\r\n\r\n");
}

int main() {
    printf("Content-Type: text/html\r\n\r\n");

    // Check if this is a POST request and handle it
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        // Display the form for message submission
        printf("<html><body>");
        printf("<form action=\"/\" method=\"post\">");
        printf("Username: <input type=\"text\" name=\"HTTP_POST_USERNAME\"><br>");
        printf("Message: <input type=\"text\" name=\"HTTP_POST_MESSAGE\"><br>");
        printf("<input type=\"submit\" value=\"Submit\">");
        printf("</form>");
        printf("</body></html>");
    }

    return 0;
}