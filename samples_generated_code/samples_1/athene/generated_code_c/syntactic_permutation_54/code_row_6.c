#include <stdio.h>
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
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Content-Type: text/html\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password</p>");
        printf("</body></html>");
    }
}