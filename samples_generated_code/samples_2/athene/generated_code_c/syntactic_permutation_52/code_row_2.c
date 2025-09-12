#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        setenv("SESSION_USERNAME", username, 1);
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
    printf("<html><body>Welcome! Please <a href=\"/login\">login</a>.</body></html>");
}

void secret_page() {
    const char *session_username = getenv("SESSION_USERNAME");
    if (session_username != NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Welcome %s! This is the <strong>Secret settings</strong> page.</body></html>", session_username);
    } else {
        printf("Location: /login\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You need to login first. Redirecting...</body></html>");
    }
}

int main() {
    const char *path_info = getenv("PATH_INFO");
    if (strcmp(path_info, "/login") == 0) {
        const char *username = getenv("HTTP_USERNAME");
        const char *password = getenv("HTTP_PASSWORD");
        do_login(username, password);
    } else if (strcmp(path_info, "/secret") == 0) {
        secret_page();
    } else {
        index_page();
    }
    return 0;
}