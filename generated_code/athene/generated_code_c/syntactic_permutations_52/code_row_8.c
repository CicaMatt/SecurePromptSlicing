#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\r\n");
        printf("Set-Cookie: username=%s; Path=/\r\n", username);
        printf("Location: /secret\r\n");
        printf("\r\n");
    } else {
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<p>Invalid credentials. Please try again.</p>");
        printf("<a href=\"/login\">Login</a>");
        printf("</body></html>");
    }
}

void index() {
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<a href=\"/login\">Login Page</a>");
    printf("</body></html>");
}

void secret() {
    char *username = getenv("HTTP_COOKIE");
    if (username && strstr(username, "username=")) {
        username = strchr(username, '=') + 1;
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<p>Secret settings</p>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\r\n");
        printf("Location: /login\r\n");
        printf("\r\n");
    }
}

int main() {
    const char *script_name = getenv("SCRIPT_NAME");

    if (strcmp(script_name, "/login") == 0) {
        char username[100], password[100];
        sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strcmp(script_name, "/index") == 0) {
        index();
    } else if (strcmp(script_name, "/secret") == 0) {
        secret();
    }

    return 0;
}