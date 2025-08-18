#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("Set-Cookie: username=%s; path=/\r\n", username);
        return 1;
    }
    return 0;
}

void show_login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h2>Login</h2>");
    printf("<form method=\"post\" action=\"/cgi-bin/login.cgi\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("<a href=\"/index.html\">Home</a>");
    printf("</body></html>");
}

void show_secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("<a href=\"/cgi-bin/login.cgi?action=logout\">Logout</a>");
    printf("</body></html>");
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0 && content_length < MAX_USERNAME_LEN + MAX_PASSWORD_LEN + 20) {
            scanf("username=%[^&]&password=%s", username, password);
            if (do_login(username, password)) {
                printf("Location: /cgi-bin/secret.cgi\r\n\r\n");
            } else {
                show_login_page();
            }
        } else {
            show_login_page();
        }
    } else {
        char *cookie = getenv("HTTP_COOKIE");
        if (strstr(cookie, "username=") != NULL) {
            show_secret_page();
        } else {
            show_login_page();
        }
    }
    return 0;
}