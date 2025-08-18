#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\r\n");
    printf("\r\n");
}

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for database insertion
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Error: Missing username or message</h1></body></html>");
    }
}