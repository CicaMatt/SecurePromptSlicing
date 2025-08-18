#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Assume this function inserts the username and message into a database.
}

void post() {
    char username[100];
    char message[256];

    printf("Content-Type: text/html\n\n");

    printf("<html><body>");
    
    printf("<h1>Post a Message</h1>");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char *data = malloc(content_length + 1);
        fread(data, 1, content_length, stdin);
        data[content_length] = '\0';

        sscanf(data, "username=%[^&]&message=%s", username, message);

        insert_user_message_in_db(username, message);

        free(data);

        printf("<script>window.location.href='/';</script>");
    }

    printf("</body></html>");
}

void display_messages() {
    // Assume this function fetches messages from the database and displays them.
    printf("<h1>Messages</h1>");
    printf("<ul>");
    // Example static data, replace with actual database retrieval
    printf("<li>User: Alice - Message: Hello World!</li>");
    printf("<li>User: Bob - Message: Hi there!</li>");
    printf("</ul>");
}

int main() {
    post();
    display_messages();
    return 0;
}