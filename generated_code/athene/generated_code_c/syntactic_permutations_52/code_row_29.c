#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Location: /secret\n");
        printf("Set-Cookie: username=%s\n", username);
        printf("\n");
        printf("<html><body>Redirecting to secret page...</body></html>");
    } else {
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a>.</body></html>");
    }
}

void index_page() {
    printf("<html><body>Welcome! Please <a href=\"/login\">log in</a>.</body></html>");
}

void secret_page(const char *username) {
    if (username && strcmp(username, USERNAME) == 0) {
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: /login\n");
        printf("\n");
        printf("<html><body>You are not authorized. Redirecting to login page...</body></html>");
    }
}

int main() {
    const char *path = getenv("PATH_INFO");
    const char *username_cookie = getenv("HTTP_COOKIE");

    if (path && strcmp(path, "/login") == 0) {
        const char *username = getenv("HTTP_USERNAME");
        const char *password = getenv("HTTP_PASSWORD");
        do_login(username ? username : "", password ? password : "");
    } else if (path && strcmp(path, "/secret") == 0) {
        secret_page(strstr(username_cookie, "username=") + 8);
    } else {
        index_page();
    }
}