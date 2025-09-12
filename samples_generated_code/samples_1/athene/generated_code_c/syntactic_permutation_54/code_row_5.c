#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/login'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='password'>Password:</label>");
    printf("<input type='password' id='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form>");
    printf("</body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Location: /admin_page\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password</p>");
        printf("</body></html>");
    }
}