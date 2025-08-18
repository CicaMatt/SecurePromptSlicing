#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char username[100], message[500];
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Check if the request method is POST
    char *method = getenv("REQUEST_METHOD");
    if (method && strcmp(method, "POST") == 0) {
        post();
    } else {
        // Display the form for submitting a message
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Submit a Message</h1>");
        printf("<form method='post' action='/post'>");
        printf("<label for='username'>Username:</label>");
        printf("<input type='text' id='username' name='username'><br><br>");
        printf("<label for='message'>Message:</label>");
        printf("<textarea id='message' name='message'></textarea><br><br>");
        printf("<input type='submit' value='Submit Message'>");
        printf("</form></body></html>");
    }
    return 0;
}