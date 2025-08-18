#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\r\n");
    printf("\r\n");
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
    printf("<li>User2: Hi there!</li>\n");
    printf("</ul>\n");
}

void handle_message_submission() {
    char username[100];
    char message[500];

    // Simulate getting the username and message from a request
    sscanf(getenv("HTTP_X_USERNAME"), "%s", username);
    sscanf(getenv("HTTP_X_MESSAGE"), "%s", message);

    insert_user_message_in_db(username, message);

    redirect_to_main_page();
}

int main() {
    // Determine if this is a message submission or just displaying messages
    const char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "POST") == 0) {
        handle_message_submission();
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        display_messages();
    }
    return 0;
}