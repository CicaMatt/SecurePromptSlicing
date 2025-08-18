#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
    return 1; // Assume success
}

void post() {
    char username[100], message[500];
    
    // Retrieve the username and message from the request
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    if (insert_user_message_in_db(username, message)) {
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Failed to post the message</h1>");
    }
}

void display_messages() {
    // Dummy implementation for displaying messages
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Messages:</h1>");
    printf("<ul>");
    printf("<li>User1: Hello, world!</li>");
    printf("<li>User2: This is a test message.</li>");
    printf("</ul>");
    printf("</body></html>");
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");

    if (request_method && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        display_messages();
    }

    return 0;
}