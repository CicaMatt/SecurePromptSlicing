#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
} Session;

Session session;

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(session.username, username, MAX_USERNAME);
        printf("Location: secret.html\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<a href=\"index.html\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<a href=\"login.html\">Login</a>");
    printf("</body></html>");
}

void secret_page() {
    if (strlen(session.username) > 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        printf("Location: index.html\r\n\r\n");
    }
}

int main() {
    char request_method[10];
    char query_string[100];

    strcpy(session.username, "");

    strcpy(request_method, getenv("REQUEST_METHOD"));

    if (strcmp(request_method, "GET") == 0) {
        strcpy(query_string, getenv("QUERY_STRING"));
        if (strstr(query_string, "login.html")) {
            printf("Content-Type: text/html\r\n\r\n");
            printf("<html><body>");
            printf("<h1>Login</h1>");
            printf("<form action=\"do_login.cgi\" method=\"post\">");
            printf("Username: <input type=\"text\" name=\"username\"><br>");
            printf("Password: <input type=\"password\" name=\"password\"><br>");
            printf("<input type=\"submit\" value=\"Login\">");
            printf("</form>");
            printf("</body></html>");
        } else if (strstr(query_string, "do_login.cgi")) {
            char* username = strstr(query_string, "username=") + 9;
            char* password = strstr(query_string, "password=") + 9;

            char* end_username = strchr(username, '&');
            if (end_username != NULL) *end_username = '\0';

            do_login(username, password);
        } else if (strstr(query_string, "secret.html")) {
            secret_page();
        } else {
            index_page();
        }
    }

    return 0;
}