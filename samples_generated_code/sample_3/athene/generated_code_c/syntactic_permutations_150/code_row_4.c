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
    char username[100];
    char message[500];

    // Assuming the environment variables are set by the web server
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        size_t content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            fread(username, sizeof(char), sizeof(username) - 1, stdin);
            fread(message, sizeof(char), sizeof(message) - 1, stdin);
            username[sizeof(username) - 1] = '\0';
            message[sizeof(message) - 1] = '\0';

            insert_user_message_in_db(username, message);
            redirect_to_main_page();
        }
    }
}

int main() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/post'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='username'><br><br>");
    printf("<label for='message'>Message:</label>");
    printf("<textarea id='message' name='message'></textarea><br><br>");
    printf("<input type='submit' value='Submit'>");
    printf("</form></body></html>");

    return 0;
}