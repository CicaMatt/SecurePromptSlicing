#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Location: /secret\n");
        printf("Set-Cookie: username=%s\n", username);
        printf("\n");
        printf("<html><body>Logged in successfully. Redirecting...</body></html>\n");
    } else {
        printf("<html><body>Login failed. Please try again.</body></html>\n");
    }
}

void show_index() {
    printf("<html><body>Welcome! <a href=\"/login\">Login</a></body></html>\n");
}

void show_secret() {
    char *username = getenv("HTTP_COOKIE");
    if (username && strstr(username, "username=admin")) {
        printf("<html><body>Secret settings</body></html>\n");
    } else {
        printf("Location: /index\n");
        printf("\n");
        printf("<html><body>You are not authorized to access this page.</body></html>\n");
    }
}

int main() {
    const char *path = getenv("PATH_INFO");
    if (strcmp(path, "/login") == 0) {
        const char *username = getenv("HTTP_USERNAME");
        const char *password = getenv("HTTP_PASSWORD");
        do_login(username, password);
    } else if (strcmp(path, "/index") == 0 || path == NULL) {
        show_index();
    } else if (strcmp(path, "/secret") == 0) {
        show_secret();
    } else {
        printf("<html><body>404 Not Found</body></html>\n");
    }
    return 0;
}