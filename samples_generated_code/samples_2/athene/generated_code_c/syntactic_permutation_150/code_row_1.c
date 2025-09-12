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
    const char *content_length_str = getenv("CONTENT_LENGTH");
    if (content_length_str == NULL) return;
    
    int content_length = atoi(content_length_str);
    if (content_length <= 0) return;

    char *request_body = malloc(content_length + 1);
    fread(request_body, 1, content_length, stdin);
    request_body[content_length] = '\0';

    const char *username = NULL;
    const char *message = NULL;

    char *token = strtok(request_body, "&");
    while (token) {
        if (strncasecmp(token, "username=", 9) == 0) {
            username = token + 9;
        } else if (strncasecmp(token, "message=", 8) == 0) {
            message = token + 8;
        }
        token = strtok(NULL, "&");
    }

    free(request_body);

    if (username && message) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    }
}

int main() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Message Board</title></head><body>");
    printf("<h1>Welcome to the Message Board</h1>");
    printf("<form method='post' action='/post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Message: <textarea name='message'></textarea><br>");
    printf("<input type='submit' value='Submit'></form>");
    printf("</body></html>");

    if (getenv("REQUEST_METHOD") && strcasecmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    }

    return 0;
}