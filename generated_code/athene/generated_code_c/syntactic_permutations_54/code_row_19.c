#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password123"

void login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form method='post' action='/login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void handle_login(const char *username, const char *password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Location: /admin_page\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome Admin!</h1>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password</p>");
        printf("<a href='/login'>Try again</a>");
        printf("</body></html>");
    }
}