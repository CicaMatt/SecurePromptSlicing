#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char *content_length_str = getenv("CONTENT_LENGTH");
    int content_length = content_length_str ? atoi(content_length_str) : 0;
    if (content_length > 0) {
        char post_data[1024];
        fread(post_data, 1, content_length, stdin);
        post_data[content_length] = '\0';

        char username[50], password[50];
        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            printf("Location: admin_page\n\n");
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("Invalid username or password.");
            printf("</body></html>");
        }
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        do_login();
    }

    return 0;
}