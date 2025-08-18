#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: username=%s\n", username);
        printf("Location: /secret\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><meta http-equiv='refresh' content='0;url=/secret'></head></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid username or password</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void secret_page() {
    char *username = getenv("HTTP_COOKIE");
    if (username != NULL && strstr(username, "username=") != NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: /index\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><meta http-equiv='refresh' content='0;url=/index'></head></html>");
    }
}

int main() {
    const char *path_info = getenv("PATH_INFO");
    if (path_info == NULL) path_info = "";

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