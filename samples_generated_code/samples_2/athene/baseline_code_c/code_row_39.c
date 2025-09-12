#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome to the Admin Page</h1>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password. Please try again.</p>");
        printf("<a href='/login'>Return to login page</a>");
        printf("</body></html>");
    }
}