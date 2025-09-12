#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-type: text/html\r\n\r\n");
    printf("<html>\n");
    printf("<head><title>Login</title></head>\n");
    printf("<body>\n");
    printf("<h1>Login Form</h1>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Password: <input type=\"password\" name=\"password\"><br>\n");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

void do_login() {
    char *username = getenv("HTTP_POST_USERNAME");
    char *password = getenv("HTTP_POST_PASSWORD");

    if (username && password) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            printf("Location: /admin_page\r\n\r\n");
            return;
        }
    }

    printf("Content-type: text/html\r\n\r\n");
    printf("<html>\n");
    printf("<head><title>Login Failed</title></head>\n");
    printf("<body>\n");
    printf("<h1>Invalid username or password</h1>\n");
    printf("<a href=\"/login\">Try again</a>\n");
    printf("</body></html>\n");
}