#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void post() {
    char username[100];
    char message[500];

    // Retrieve the username and message from the request (assuming POST data)
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

void display_messages() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    // Dummy implementation for displaying messages
    printf("<li>User: John Doe, Message: Hello World!</li>");
    printf("</ul>");
    printf("</body></html>");
}

int main() {
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    } else {
        display_messages();
    }
    return 0;
}