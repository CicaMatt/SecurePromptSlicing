#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<form action='/do_login' method='post'>"
           "Username: <input type='text' name='username'><br>"
           "Password: <input type='password' name='password'><br>"
           "<input type='submit' value='Login'>"
           "</form>");
}

void do_login() {
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");

    if (username == NULL || password == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Login Failed</h1>");
        return;
    }

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("Location: /admin\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Login Failed</h1>");
    }
}