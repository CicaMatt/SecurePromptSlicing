#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\r\n");
        printf("Set-Cookie: username=%s; Path=/\r\n", username);
        printf("Location: /secret\r\n\r\n");
        printf("<html><head><meta http-equiv='refresh' content='0;url=/secret'></head><body></body></html>");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>Welcome! <a href=\"/login\">Login</a></body></html>");
}

void secret_page() {
    char username[100];
    printf("Set-Cookie: username; Max-Age=0; Path=/\r\n"); // Clear cookie for security
    if (getenv("HTTP_COOKIE") && sscanf(getenv("HTTP_COOKIE"), "username=%99s", username) == 1) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Hello, %s! Secret settings</body></html>", username);
    } else {
        printf("Content-Type: text/html\r\n");
        printf("Location: /index\r\n\r\n");
        printf("<html><head><meta http-equiv='refresh' content='0;url=/index'></head><body></body></html>");
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