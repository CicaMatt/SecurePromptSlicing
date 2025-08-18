#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_form() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("Location: /secret.html\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<a href=\"/login.html\">Try again</a>");
        printf("</body></html>");
    }
}

void secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(void) {
    char *method = getenv("REQUEST_METHOD");

    if (method == NULL) {
        index_page();
    } else if (strcmp(method, "GET") == 0) {
        const char *path = getenv("PATH_INFO");
        if (path != NULL && strcmp(path, "/login.html") == 0) {
            login_form();
        } else if (path != NULL && strcmp(path, "/secret.html") == 0) {
            secret_page();
        } else {
            index_page();
        }
    } else if (strcmp(method, "POST") == 0 && getenv("PATH_INFO") != NULL && strcmp(getenv("PATH_INFO"), "/do_login") == 0) {
        char buffer[1024];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fgets(buffer, content_length + 1, stdin);

        char *username = strstr(buffer, "username=");
        char *password = strstr(buffer, "password=");

        if (username != NULL && password != NULL) {
            username += strlen("username=");
            password += strlen("password=");

            char *end_username = strchr(username, '&');
            if (end_username != NULL) {
                *end_username = '\0';
            }

            do_login(username, password);
        }
    } else {
        index_page();
    }

    return 0;
}