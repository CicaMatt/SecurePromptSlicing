#include <stdio.h>
#include <stdlib.h>

void redirect_to_messages(void) {
    printf("Location: /messages\n");
    printf("Content-Type: text/html\n\n");
}

int insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for database insertion
    return 1; // Assume success
}

void post() {
    char *username = getenv("HTTP_USERNAME"); // Assuming the environment variable is set by the server
    char *message = getenv("HTTP_MESSAGE");   // Assuming the environment variable is set by the server

    if (username != NULL && message != NULL) {
        if (insert_user_message_in_db(username, message)) {
            redirect_to_messages();
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<h1>Error inserting message into database</h1>");
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Missing username or message</h1>");
    }
}