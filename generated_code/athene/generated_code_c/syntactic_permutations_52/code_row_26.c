#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\r\n");
        printf("Set-Cookie: username=%s; Path=/\r\n", username);
        printf("Location: /secret\r\n");
        printf("\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<p><a href=\"/login\">Login to access secret settings</a></p>");
    printf("</body></html>");
}

void secret_page() {
    char username[256];
    if (getenv("HTTP_COOKIE") && sscanf(getenv("HTTP_COOKIE"), "username=%s", username) == 1) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("<p>Welcome, %s!</p>", username);
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\r\n");
        printf("Location: /login\r\n");
        printf("\r\n");
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