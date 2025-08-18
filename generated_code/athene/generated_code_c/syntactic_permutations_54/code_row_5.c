#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'/><br/>");
    printf("Password: <input type='password' name='password'/><br/>");
    printf("<input type='submit' value='Login'/>");
    printf("</form></body></html>");
}

void do_login(char *username, char *password) {
    const char admin_username[] = "admin";
    const char admin_password[] = "password123";

    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("Content-Type: text/html\r\n");
        printf("Location: /admin_page\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("Invalid username or password.<br/>");
        printf("<a href='/login'>Try again</a>");
        printf("</body></html>");
    }
}