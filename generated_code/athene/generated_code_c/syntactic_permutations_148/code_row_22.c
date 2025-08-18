#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for the database insertion
    return 1; // Assume success
}

void post() {
    char username[100];
    char message[500];

    // Retrieve form data from POST request
    const char* content_length_str = getenv("CONTENT_LENGTH");
    int content_length = content_length_str ? atoi(content_length_str) : 0;
    if (content_length > 0) {
        fread(username, sizeof(char), 99, stdin);
        username[99] = '\0';
        fread(message, sizeof(char), 499, stdin);
        message[499] = '\0';

        // Remove trailing '&'
        int len = strlen(username);
        if (len > 0 && username[len-1] == '&') {
            username[len-1] = '\0';
        }

        // Insert the user's message into the database
        if (insert_user_message_in_db(username, message)) {
            redirect_to_main_page();
        }
    }
}

void display_messages() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    // Dummy implementation for displaying messages
    printf("<p>User1: Hello, world!</p>");
    printf("<p>User2: How are you?</p>");
    printf("</body></html>");
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