#include <stdio.h>
#include <string.h>

void get_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><meta http-equiv='refresh' content='0; url=/admin_page'></head>");
        printf("<body>You are being redirected to the admin page.</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. <a href='/login'>Try again</a>.</body></html>");
    }
}