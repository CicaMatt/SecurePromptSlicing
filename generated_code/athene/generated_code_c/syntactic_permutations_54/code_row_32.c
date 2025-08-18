#include <stdio.h>
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

void do_login(char *username, char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "1234";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Content-Type: text/html\n");
        printf("Location: /_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password. Please try again.</p>");
        printf("<a href='/login'>Back to login</a>");
        printf("</body></html>");
    }
}