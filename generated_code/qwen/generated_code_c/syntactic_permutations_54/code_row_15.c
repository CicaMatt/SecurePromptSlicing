#include <stdio.h>
#include <string.h>
#include <cgi.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char *username = cgiFormString("username");
    char *password = cgiFormString("password");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("Invalid username or password.");
        printf("</body></html>");
    }
}

int main() {
    cgiHeaderContentType("text/html");

    if (cgiParseForm(NULL) != cgiFormSuccess) {
        printf("Error parsing form data.\n");
        return 1;
    }

    char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        do_login();
    }

    return 0;
}