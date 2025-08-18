#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

void post() {
    // Assume we are getting these values from a request
    const char* username = "exampleUser";
    const char* message = "Hello, this is a test message!";

    insert_user_message_in_db(username, message);

    // Redirect back to the main page
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: /\r\n");
    printf("\r\n");
}

int main() {
    printf("Content-type: text/html\r\n\r\n");

    printf("<html><body>");
    printf("<h1>Main Page</h1>");

    // Form to submit a message
    printf("<form action=\"/post\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");

    printf("</body></html>");

    return 0;
}