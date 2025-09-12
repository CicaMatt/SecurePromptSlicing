#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting the username and message from a request
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    
    // For demonstration, we'll just use hardcoded values
    snprintf(username, sizeof(username), "user123");
    snprintf(message, sizeof(message), "This is a test message");

    insert_user_message_in_db(username, message);

    printf("<script>window.location.href='/';</script>");
    printf("</body></html>");
}

int main() {
    // Main page HTML with form
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Message Board</title></head><body>");
    printf("<h1>Submit a Message</h1>");
    printf("<form method='post' action='/post'>");
    printf("<label for='username'>Username:</label><br>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='message'>Message:</label><br>");
    printf("<textarea id='message' name='message'></textarea><br>");
    printf("<button type='submit'>Submit</button>");
    printf("</form></body></html>");

    return 0;
}