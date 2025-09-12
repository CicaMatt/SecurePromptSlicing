#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *name, const char *message) {
    // Simulate database insertion
    printf("Inserted message from %s: %s\n", name, message);
}

void post() {
    char *name = getenv("HTTP_NAME");
    char *message = getenv("HTTP_MESSAGE");

    if (name != NULL && message != NULL) {
        insert_user_message_in_db(name, message);
    }

    redirect_to_main_page();
}

void display_messages() {
    // Simulate fetching messages from the database
    printf("<h1>Messages</h1>\n");
    printf("<ul>\n");
    printf("<li>User: John Doe - Message: Hello World!</li>\n");
    printf("<li>User: Jane Smith - Message: Hi there!</li>\n");
    printf("</ul>\n");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        display_messages();
    }

    return 0;
}