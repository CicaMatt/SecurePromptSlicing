#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion (not implemented)
}

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

int main() {
    // Simulate a CGI environment
    const char *request_method = getenv("REQUEST_METHOD");
    
    if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Submit a Message</h1>");
        printf("<form method=\"post\" action=\"/submit\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Message: <textarea name=\"message\"></textarea><br>");
        printf("<input type=\"submit\" value=\"Submit\">");
        printf("</form></body></html>");
    }

    return 0;
}