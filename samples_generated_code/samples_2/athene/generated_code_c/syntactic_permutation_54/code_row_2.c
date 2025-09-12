#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(char* username, char* password) {
    const char admin_username[] = "admin";
    const char admin_password[] = "admin123";

    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("Content-Type: text/html\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Login failed. Please try again.</p>");
        printf("</body></html>");
    }
}