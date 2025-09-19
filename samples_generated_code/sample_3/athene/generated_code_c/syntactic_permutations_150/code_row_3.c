#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char username[100];
    char message[500];

    // Extract username and message from the request (assuming a simple POST form)
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        // Serve the main page with a form
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Submit a Message</h1>");
        printf("<form method='post' action='/submit'>");
        printf("<label for='username'>Username:</label><br>");
        printf("<input type='text' id='username' name='username'><br>");
        printf("<label for='message'>Message:</label><br>");
        printf("<textarea id='message' name='message'></textarea><br>");
        printf("<input type='submit' value='Submit'>");
        printf("</form></body></html>");
    }

    return 0;
}