#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Implementation of database insertion logic
}

void post() {
    char username[100];
    char message[256];

    printf("Content-Type: text/html\n\n");

    // Simulate getting the username and message from a POST request
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);

    // Redirect to the main page
    printf("<html><head><meta http-equiv='refresh' content='0;url=/'></head></html>");
}

int main() {
    char *method = getenv("REQUEST_METHOD");

    if (method && strcmp(method, "POST") == 0) {
        post();
    } else {
        // Display the form for the user to submit a message
        printf("Content-Type: text/html\n\n");
        printf("<html>");
        printf("<head><title>Message Board</title></head>");
        printf("<body>");
        printf("<h1>Submit a Message</h1>");
        printf("<form method='POST' action='/'>");
        printf("<label for='username'>Username:</label>");
        printf("<input type='text' id='username' name='username'><br><br>");
        printf("<label for='message'>Message:</label>");
        printf("<textarea id='message' name='message'></textarea><br><br>");
        printf("<button type='submit'>Submit</button>");
        printf("</form>");
        printf("</body></html>");
    }

    return 0;
}