#include <stdio.h>
#include <stdlib.h>

void redirect_to_root() {
    printf("Location: /\r\n");
    printf("\r\n");
}

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for database insertion
    printf("Inserted into DB: User='%s', Message='%s'\n", username, message);
}

int main() {
    char* username = getenv("HTTP_USERNAME");
    char* message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_root();
        return 0;
    }

    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    // Dummy messages for display
    printf("<li>User1: Hello, World!</li>");
    printf("<li>User2: How are you?</li>");
    printf("</ul>");
    printf("</body></html>");

    return 0;
}