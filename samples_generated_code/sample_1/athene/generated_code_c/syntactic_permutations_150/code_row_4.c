#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a POST request
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    } else {
        // Serve the main page with a form
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Submit a Message</h1>");
        printf("<form method='post' action='/post'>");
        printf("<label for='username'>Username:</label>");
        printf("<input type='text' id='username' name='username'><br><br>");
        printf("<label for='message'>Message:</label>");
        printf("<textarea id='message' name='message'></textarea><br><br>");
        printf("<button type='submit'>Submit</button>");
        printf("</form></body></html>");
    }
    return 0;
}