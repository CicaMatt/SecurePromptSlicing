#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "1234"

typedef struct {
    char username[50];
} Session;

Session session;

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        strcpy(session.username, username);
        printf("Location: /secret\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Redirecting to secret page...</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Welcome! <a href=\"/login\">Login</a></body></html>");
}

void secret_page() {
    if (strlen(session.username) > 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Secret settings. Logged in as %s.</body></html>", session.username);
    } else {
        printf("Location: /index\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are not logged in. Redirecting to index page...</body></html>");
    }
}

int main() {
    char *uri = getenv("REQUEST_URI");
    if (strcmp(uri, "/") == 0) {
        index_page();
    } else if (strcmp(uri, "/login") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<form method=\"post\" action=\"/do_login\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Password: <input type=\"password\" name=\"password\"><br>");
        printf("<input type=\"submit\" value=\"Login\">");
        printf("</form></body></html>");
    } else if (strcmp(uri, "/do_login") == 0) {
        char username[50], password[50];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), 50, stdin);
        fread(password, sizeof(char), 50, stdin);
        do_login(username, password);
    } else if (strcmp(uri, "/secret") == 0) {
        secret_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>404 Not Found</body></html>");
    }
    return 0;
}