#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<form action='/do_login' method='post'>"
           "Username: <input type='text' name='username'><br>"
           "Password: <input type='password' name='password'><br>"
           "<input type='submit' value='Login'>"
           "</form>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<p>Login failed. Please try again.</p>");
    }
}