#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into DB: User = %s, Message = %s\n", username, message);
}

// Function to handle form submission
void post() {
    char* username = getenv("HTTP_POST_USERNAME");
    char* message = getenv("HTTP_POST_MESSAGE");

    if (username == NULL || message == NULL) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Error: Missing username or message</h1></body></html>");
        return;
    }

    insert_user_message_in_db(username, message);

    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body><h1>Message submitted successfully!</h1><a href=\"/\">Go back</a></body></html>");
}

int main() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form action=\"post.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"HTTP_POST_USERNAME\"><br>");
    printf("Message: <textarea name=\"HTTP_POST_MESSAGE\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");

    return 0;
}