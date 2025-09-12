#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password</p>");
        printf("</body></html>");
    }
}

int main() {
    char* request_method = getenv("REQUEST_METHOD");

    if (request_method != NULL) {
        if (strcmp(request_method, "GET") == 0) {
            login();
        } else if (strcmp(request_method, "POST") == 0) {
            char buffer[1024];
            int content_length = atoi(getenv("CONTENT_LENGTH"));
            fread(buffer, 1, content_length, stdin);
            buffer[content_length] = '\0';

            char* username = strtok(buffer, "&");
            username = strchr(username, '=') + 1;

            char* password = strtok(NULL, "&");
            password = strchr(password, '=') + 1;

            do_login(username, password);
        }
    }

    return 0;
}