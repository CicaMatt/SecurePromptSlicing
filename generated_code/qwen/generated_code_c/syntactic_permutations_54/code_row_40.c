#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

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
        printf("Status: 302 Moved Temporarily\n");
        printf("Location: /\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("Invalid username or password.");
        printf("</body></html>");
    }
}

int main() {
    char request_method[10];
    char content_length_str[10];
    int content_length;
    char* post_data = NULL;

    strcpy(request_method, getenv("REQUEST_METHOD"));

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        content_length_str[0] = '\0';
        strcpy(content_length_str, getenv("CONTENT_LENGTH"));
        content_length = atoi(content_length_str);

        post_data = malloc(content_length + 1);
        if (!post_data) return 1;

        fread(post_data, content_length, 1, stdin);
        post_data[content_length] = '\0';

        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];

        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        do_login(username, password);

        free(post_data);
    }

    return 0;
}