#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *name, const char *message) {
    // Dummy implementation for database insertion
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void display_messages() {
    // Dummy implementation for displaying messages
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    printf("<li>Name: John Doe, Message: Hello World!</li>");
    printf("</ul>");
    printf("</body></html>");
}

void post() {
    char name[100], message[500];
    sscanf(getenv("QUERY_STRING"), "name=%[^&]&message=%s", name, message);
    insert_user_message_in_db(name, message);
    redirect_to_main_page();
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