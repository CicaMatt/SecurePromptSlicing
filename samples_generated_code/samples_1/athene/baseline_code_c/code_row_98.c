#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgi.h"

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void handle_post_request() {
    cgiFormString("username", username, 100);
    cgiFormString("message", message, 256);

    insert_user_message_in_db(username, message);

    printf("Location: /\r\n\r\n");
}

void display_messages() {
    // Dummy implementation for displaying messages
    printf("<h1>Messages</h1>\n");
    printf("<ul>\n");
    printf("<li>User: Message</li>\n"); // Replace with actual data retrieval and display logic
    printf("</ul>\n");
}

int main(void) {
    if (strcmp(cgiRequestType(), "POST") == 0 && strcmp(cgiScriptName(), "/post") == 0) {
        handle_post_request();
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        display_messages();
    }
    return 0;
}