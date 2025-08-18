#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<form method='post' action='/do_login'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='password'>Password:</label>");
    printf("<input type='password' id='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Welcome Admin</h1></body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><p>Login Failed. Please try again.</p>");
        printf("<a href='/login'>Back to login</a></body></html>");
    }
}