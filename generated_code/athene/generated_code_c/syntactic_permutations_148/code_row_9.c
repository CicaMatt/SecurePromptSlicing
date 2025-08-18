#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\n");
    printf("\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
    printf("Inserted message from %s: %s\n", username, message);
}

void display_messages() {
    // Dummy implementation for displaying messages
    printf("<h1>Messages</h1>\n");
    printf("<ul>\n");
    printf("<li>User1: Hello World!</li>\n");
    printf("<li>User2: How are you?</li>\n");
    printf("</ul>\n");
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Error</h1>\n");
        printf("<p>Username or message not provided.</p>\n");
    }
}

int main() {
    post();
    display_messages();
    return 0;
}