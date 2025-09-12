#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\r\n");
        printf("Set-Cookie: username=%s; Path=/\r\n", username);
        printf("Location: /secret\r\n\r\n");
        printf("<html><head><meta http-equiv='refresh' content='0;url=/secret'></head></html>");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a></body></html>");
    }
}

void login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><head><title>Login</title></head><body>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form></body></html>");
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><head><title>Index</title></head><body>");
    printf("<a href=\"/login\">Login</a></body></html>");
}

void secret_page(const char *username) {
    if (strcmp(username, USERNAME) == 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><head><title>Secret Settings</title></head><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        login_page();
    }
}

int main(int argc, char **argv) {
    const char *path_info = getenv("PATH_INFO");
    const char *cookie = getenv("HTTP_COOKIE");

    if (path_info == NULL || strcmp(path_info, "/") == 0) {
        index_page();
    } else if (strcmp(path_info, "/login") == 0) {
        login_page();
    } else if (strcmp(path_info, "/do_login") == 0) {
        const char *username = getenv("HTTP_USERNAME");
        const char *password = getenv("HTTP_PASSWORD");
        do_login(username, password);
    } else if (strcmp(path_info, "/secret") == 0) {
        const char *username = strstr(cookie, "username=");
        if (username != NULL) {
            username += 8; // Skip "username="
            char *semicolon = strchr(username, ';');
            if (semicolon != NULL) {
                *semicolon = '\0';
            }
            secret_page(username);
        } else {
            login_page();
        }
    }

    return 0;
}