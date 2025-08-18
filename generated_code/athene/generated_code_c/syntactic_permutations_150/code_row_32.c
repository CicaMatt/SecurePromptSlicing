#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
    printf("Inserting message from user %s: %s\n", username, message);
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a POST request (in real code, use CGI or similar)
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        size_t content_length = atoi(getenv("CONTENT_LENGTH"));
        int i = 0;
        char c;

        while (i < content_length && (c = getchar()) != EOF) {
            if (c == '&' || c == '=') c = '\n';
            if (i < sizeof(username) - 1) username[i] = c;
            else if (i < sizeof(username) + sizeof(message)) message[i - sizeof(username)] = c;
            i++;
        }
        username[sizeof(username) - 1] = '\0';
        message[sizeof(message) - 1] = '\0';

        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
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

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    }

    return 0;
}