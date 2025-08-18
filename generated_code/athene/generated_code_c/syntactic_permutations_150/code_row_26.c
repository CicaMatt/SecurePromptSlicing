#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void post() {
    char username[100];
    char message[500];

    // Retrieve the username and message from the request
    sscanf(getenv("QUERY_STRING"), "username=%99[^&]&message=%499s", username, message);

    // Insert the user message into the database
    insert_user_message_in_db(username, message);

    // Redirect to the main page
    redirect_to_main_page();
}

void print_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method=\"POST\" action=\"/post\">");
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
    printf("<label for=\"message\">Message:</label>");
    printf("<input type=\"text\" id=\"message\" name=\"message\"><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form></body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        print_form();
    }

    return 0;
}