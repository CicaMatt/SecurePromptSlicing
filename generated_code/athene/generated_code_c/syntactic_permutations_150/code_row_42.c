#include <stdio.h>
#include <stdlib.h>

void redirect_user(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function for database insertion
}

void post() {
    char username[100];
    char message[500];

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            fread(username, sizeof(char), 99, stdin);
            username[99] = '\0';
            fread(message, sizeof(char), 499, stdin);
            message[499] = '\0';

            insert_user_message_in_db(username, message);
        }
    }

    redirect_user("/");
}

int main() {
    printf("Content-Type: text/html\n\n");

    printf("<html><body>");
    printf("<form method='post' action='/submit'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='message'>Message:</label>");
    printf("<textarea id='message' name='message'></textarea><br>");
    printf("<button type='submit'>Submit</button>");
    printf("</form></body></html>");

    post();

    return 0;
}