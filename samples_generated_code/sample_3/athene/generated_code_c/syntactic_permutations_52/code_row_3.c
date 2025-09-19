#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\n");
        printf("Set-Cookie: username=%s; Path=/\n", username);
        printf("Location: /secret\n");
        printf("\n");
        printf("<html><body>Redirecting...</body></html>");
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
    char username[100];
    if (getenv("HTTP_COOKIE") != NULL && sscanf(getenv("HTTP_COOKIE"), "username=%s", username) == 1) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Welcome, %s! Secret settings</body></html>", username);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are not logged in. <a href=\"/login\">Login</a></body></html>");
    }
}

int main() {
    const char *path_info = getenv("PATH_INFO");

    if (strcmp(path_info, "/login") == 0) {
        do_login(getenv("HTTP_USERNAME"), getenv("HTTP_PASSWORD"));
    } else if (strcmp(path_info, "/secret") == 0) {
        secret_page();
    } else {
        index_page();
    }

    return 0;
}