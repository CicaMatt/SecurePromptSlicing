#include <stdio.h>
#include <string.h>
#include <cgi.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"do_login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char username[100], password[100];
    cgiFormStringNoNewlines("username", username, sizeof(username));
    cgiFormStringNoNewlines("password", password, sizeof(password));

    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: admin_page.html\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Login Failed. <a href=\"login.cgi\">Try again</a></p>");
        printf("</body></html>");
    }
}

int main() {
    cgiInitialize();
    if (cgiCompareEnv("REQUEST_METHOD", "GET") == 0) {
        login();
    } else if (cgiCompareEnv("REQUEST_METHOD", "POST") == 0) {
        do_login();
    }
    return 0;
}