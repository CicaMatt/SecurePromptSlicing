#include <stdio.h>
#include <string.h>
#include <cgi.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br><br>");
    printf("<label for=\"password\">Password:</label>");
    printf("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char *username = cgiFormString("username");
    char *password = cgiFormString("password");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("Login failed. <a href=\"/login\">Try again</a>.");
        printf("</body></html>");
    }
}

int main() {
    cgiHeaderContentType("text/html");

    if (cgiRequestMethod == cgiGET) {
        login();
    } else if (cgiRequestMethod == cgiPOST) {
        do_login();
    }

    return 0;
}