#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting the username and message from a request (e.g., form submission)
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/submit'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Message: <textarea name='message'></textarea><br>");
    printf("<input type='submit' value='Submit'>");
    printf("</form>");

    // For demonstration, we'll just use fixed values
    const char *req_username = "testuser";
    const char *req_message = "Hello, world!";

    insert_user_message_in_db(req_username, req_message);

    // Redirect the user back to the main page
    printf("<script>window.location.href='/';</script>");
    printf("</body></html>");
}

int main() {
    post();
    return 0;
}