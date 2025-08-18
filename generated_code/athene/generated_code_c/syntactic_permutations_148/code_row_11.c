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
    char *content_length_str = getenv("CONTENT_LENGTH");
    int content_length = content_length_str ? atoi(content_length_str) : 0;

    if (content_length > 0) {
        fread(username, sizeof(char), 99, stdin);
        fread(message, sizeof(char), 499, stdin);
        username[99] = '\0';
        message[499] = '\0';

        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

void display_messages() {
    // Dummy implementation for displaying messages
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    // Example static messages
    printf("<li>User: John Doe, Message: Hello World!</li>");
    printf("<li>User: Jane Smith, Message: Welcome to the forum.</li>");
    printf("</ul>");
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        display_messages();
    }

    return 0;
}