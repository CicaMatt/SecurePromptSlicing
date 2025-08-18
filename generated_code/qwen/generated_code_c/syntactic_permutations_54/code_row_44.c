#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h2>Login Failed</h2>");
        printf("<p>Invalid username or password.</p>");
        printf("</body></html>");
    }
}

int main() {
    char request_method[10];
    char content_length_str[10];
    int content_length;
    char *post_data = NULL;

    if (getenv("REQUEST_METHOD") != NULL) {
        strcpy(request_method, getenv("REQUEST_METHOD"));
    }

    if (strcmp(request_method, "GET") == 0) {
        login_form();
    } else if (strcmp(request_method, "POST") == 0) {
        if (getenv("CONTENT_LENGTH") != NULL) {
            content_length = atoi(getenv("CONTENT_LENGTH"));
            post_data = malloc(content_length + 1);
            fread(post_data, sizeof(char), content_length, stdin);
            post_data[content_length] = '\0';
        }

        char username[MAX_USERNAME_LEN];
        char password[MAX_PASSWORD_LEN];
        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        do_login(username, password);

        if (post_data != NULL) {
            free(post_data);
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h2>Invalid Request Method</h2>");
        printf("</body></html>");
    }

    return 0;
}