#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgi.h" // Assuming a CGI library is used for web routing

void insert_user_message_in_db(const char *username, const char *message) {
    // Stub function to simulate database insertion
}

void display_messages() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    // Simulate fetching and displaying messages from the database
    printf("<li>User: Alice, Message: Hello World!</li>");
    printf("<li>User: Bob, Message: Hi there!</li>");
    printf("</ul>");
    printf("</body></html>");
}

void handle_post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    // Redirect to the / route
    printf("Location: /\n\n");
}

void handle_get() {
    display_messages();
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "POST") == 0) {
        handle_post();
    } else if (strcmp(request_method, "GET") == 0) {
        handle_get();
    }

    return 0;
}