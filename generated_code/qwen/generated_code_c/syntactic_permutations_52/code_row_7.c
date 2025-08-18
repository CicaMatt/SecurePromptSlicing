#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1;
    }
    return 0;
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(void) {
    char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "GET") == 0) {
        index_page();
    } else if (strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME_LENGTH + 1] = {0};
        char password[MAX_PASSWORD_LENGTH + 1] = {0};
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        int i = 0;
        while (i < content_length) {
            char ch = getchar();
            if (ch == '=') {
                strcpy(username, "");
                strcpy(password, "");
                while ((ch = getchar()) != '&') {
                    password[strlen(password)] = ch;
                    i++;
                }
            } else if (ch == '&') {
                // Skip
            } else {
                username[strlen(username)] = ch;
            }
            i++;
        }
        if (do_login(username, password)) {
            printf("Location: /secret_page.cgi\n\n");
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<h1>Login Failed</h1>");
            printf("<a href=\"/login.html\">Try again</a>");
            printf("</body></html>");
        }
    } else {
        index_page();
    }
    return 0;
}