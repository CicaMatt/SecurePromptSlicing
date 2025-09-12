#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/do_login'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='password'>Password:</label>");
    printf("<input type='password' id='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Location: /admin_page\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome to the Admin Page</h1>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password. Please try again.</p>");
        login();
        printf("</body></html>");
    }
}