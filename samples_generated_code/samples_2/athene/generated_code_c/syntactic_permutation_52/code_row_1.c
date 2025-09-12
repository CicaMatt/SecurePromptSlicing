#include <stdio.h>
#include <string.h>

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("Set-Cookie: username=%s; Path=/\r\n", username);
        printf("Location: /secret\r\n");
        printf("\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<p>Login failed. Please try again.</p>");
        printf("<a href=\"/login\">Login</a>");
        printf("</body></html>");
    }
}

void index() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<p>Welcome! Click <a href=\"/login\">here</a> to login.</p>");
    printf("</body></html>");
}

void secret() {
    char username[100] = "";
    if (getenv("HTTP_COOKIE")) {
        sscanf(getenv("HTTP_COOKIE"), "username=%s", username);
    }
    if (strlen(username) == 0) {
        printf("Location: /index\r\n");
        printf("\r\n");
        return;
    }
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<p>Secret settings</p>");
    printf("</body></html>");
}

int main() {
    const char *path_info = getenv("PATH_INFO");
    if (strcmp(path_info, "/login") == 0) {
        const char *username = getenv("HTTP_USERNAME");
        const char *password = getenv("HTTP_PASSWORD");
        do_login(username, password);
    } else if (strcmp(path_info, "/index") == 0 || path_info == NULL) {
        index();
    } else if (strcmp(path_info, "/secret") == 0) {
        secret();
    }
    return 0;
}