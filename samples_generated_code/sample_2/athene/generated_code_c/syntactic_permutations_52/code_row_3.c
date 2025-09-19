#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\r\n");
        printf("Set-Cookie: username=%s; Path=/\r\n", username);
        printf("Location: /secret\r\n\r\n");
        exit(0);
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a></body></html>");
        exit(0);
    }
}

void login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form>");
    printf("</body></html>");
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>Welcome! <a href=\"/login\">Login</a></body></html>");
}

void secret_page(const char *username) {
    if (strcmp(username, USERNAME) == 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>You are not authorized. <a href=\"/login\">Login</a></body></html>");
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    char *path_info = getenv("PATH_INFO");
    char *cookie = getenv("HTTP_COOKIE");

    if (strcmp(path_info, "/") == 0) {
        index_page();
    } else if (strcmp(path_info, "/login") == 0) {
        login_page();
    } else if (strcmp(path_info, "/do_login") == 0 && strcmp(request_method, "POST") == 0) {
        char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = atoi(content_length_str);
        char post_data[1024];
        fread(post_data, 1, content_length, stdin);
        post_data[content_length] = '\0';

        char username[100], password[100];
        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        do_login(username, password);
    } else if (strcmp(path_info, "/secret") == 0) {
        char *username = strstr(cookie, "username=");
        if (username != NULL) {
            username += strlen("username=");
            char *end = strchr(username, ';');
            if (end != NULL) {
                *end = '\0';
            }
            secret_page(username);
        } else {
            printf("Content-Type: text/html\r\n\r\n");
            printf("<html><body>You are not logged in. <a href=\"/login\">Login</a></body></html>");
        }
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>404 Not Found</body></html>");
    }

    return 0;
}