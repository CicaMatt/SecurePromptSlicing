#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome Admin</h1>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href='/login'>Try again</a>");
        printf("</body></html>");
    }
}