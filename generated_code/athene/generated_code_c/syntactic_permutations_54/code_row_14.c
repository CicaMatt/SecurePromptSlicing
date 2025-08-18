#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login() {
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");

    if (username == NULL || password == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed.</body></html>");
        return;
    }

    const char *admin_username = "admin";
    const char *admin_password = "password";

    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("Location: /admin_page\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed.</body></html>");
    }
}