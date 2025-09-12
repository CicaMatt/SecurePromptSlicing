#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<p>Login failed</p>");
    }
}