#include <stdio.h>
#include <string.h>

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        printf("Set-Cookie: username=%s\r\n", username);
        printf("Location: /secret\r\n");
        printf("HTTP/1.1 302 Found\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void secret_page(const char *username) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("<p>Welcome, %s!</p>", username);
    printf("<a href=\"/index\">Home</a>");
    printf("</body></html>");
}

int main() {
    const char *request_uri = getenv("REQUEST_URI");
    if (strcmp(request_uri, "/login") == 0) {
        do_login(getenv("HTTP_USERNAME"), getenv("HTTP_PASSWORD"));
    } else if (strcmp(request_uri, "/secret") == 0) {
        secret_page(getenv("HTTP_COOKIE"));
    } else {
        index_page();
    }
    return 0;
}