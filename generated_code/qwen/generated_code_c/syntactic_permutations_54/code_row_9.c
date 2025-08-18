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
    char *username = cgiFormStringNoNewlines("username");
    char *password = cgiFormStringNoNewlines("password");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: admin_page.cgi\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid credentials</p>");
        printf("</body></html>");
    }
}

int main() {
    cgiHeaderContentType("text/html");

    if (cgiParseForm(NULL) == cgiFormSuccess) {
        do_login();
    } else {
        login();
    }

    return 0;
}