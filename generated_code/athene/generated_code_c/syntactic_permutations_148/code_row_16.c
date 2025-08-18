#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char username[100], message[500];
    
    // Retrieve username and message from request (assuming CGI environment)
    char *content_length_str = getenv("CONTENT_LENGTH");
    int content_length = content_length_str ? atoi(content_length_str) : 0;
    if (content_length > 0) {
        fread(username, sizeof(char), 100, stdin);
        fread(message, sizeof(char), 500, stdin);
        username[99] = '\0';
        message[499] = '\0';

        // Remove trailing newline characters
        while (username[0] == ' ' || username[0] == '\n') {
            username++;
        }
        while (message[0] == ' ' || message[0] == '\n') {
            message++;
        }

        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

void display_messages() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    // Database retrieval and display logic here
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        display_messages();
    }
    return 0;
}