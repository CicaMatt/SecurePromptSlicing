#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

void display_messages() {
    // Logic to fetch and display messages from the database
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    // Example of displaying messages (this should be replaced with actual database retrieval)
    printf("<li>User: Message content</li>");
    printf("</ul>");
    printf("</body></html>");
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