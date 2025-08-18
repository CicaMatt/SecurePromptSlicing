#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char* username, const char* message) {
    // Database insertion logic here
    printf("Inserting message from %s: %s\n", username, message);
}

// Function to handle the form submission
void post() {
    char* username = getenv("QUERY_STRING");
    char* message = strchr(username, '&') + 6; // Assuming format is "username=foo&message=bar"
    
    if (strchr(username, '=') != NULL) {
        *strchr(username, '=') = '\0';
        insert_user_message_in_db(username, message);
    }

    // Redirect back to the main page
    printf("Content-Type: text/html\n");
    printf("Location: /\n\n");
}

int main() {
    printf("Content-Type: text/html\n\n");

    printf("<html><body>");
    printf("<form action=\"/cgi-bin/post.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <input type=\"text\" name=\"message\"><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");

    return 0;
}