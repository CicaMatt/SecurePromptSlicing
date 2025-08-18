#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Stub for database insertion logic
}

void display_messages() {
    // Stub for displaying messages from the database
    printf("<h1>Messages</h1>\n");
    printf("<ul>\n");
    printf("  <li>User: Message</li>\n"); // Example message, replace with actual data retrieval
    printf("</ul>\n");
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");

    if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        display_messages();
    }

    return 0;
}