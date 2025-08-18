#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1;
    }
    return 0;
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Login Form</h2>");
    printf("<form action=\"/do_login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(void) {
    char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME], password[MAX_PASSWORD];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char input[content_length + 1];

        if (fread(input, 1, content_length, stdin) != content_length) {
            printf("Content-Type: text/plain\n\nError reading POST data");
            return 1;
        }
        input[content_length] = '\0';

        sscanf(input, "username=%[^&]&password=%s", username, password);

        if (do_login(username, password)) {
            printf("Location: /secret.cgi\n\n");
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<h2>Login Failed</h2>");
            printf("<a href=\"/login.html\">Try again</a>");
            printf("</body></html>");
        }
    } else {
        login_page();
    }

    return 0;
}