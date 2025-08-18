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
        printf("<html><head><meta http-equiv='refresh' content='0;url=/secret'></head><body></body></html>");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Login Failed. <a href=\"/login\">Try again</a></body></html>");
    }
}

void show_login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><head><title>Login Page</title></head><body>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form></body></html>");
}

void show_index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><head><title>Index Page</title></head><body>");
    printf("<a href=\"/login\">Login</a></body></html>");
}

void show_secret_page(const char *username) {
    if (strcmp(username, USERNAME) == 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>You are not authorized to view this page. <a href=\"/login\">Login</a></body></html>");
    }
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    const char *username_cookie = getenv("HTTP_COOKIE");

    if (strcmp(request_method, "GET") == 0) {
        const char *path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/login") == 0) {
            show_login_page();
        } else if (path_info && strcmp(path_info, "/secret") == 0) {
            const char *username = strstr(username_cookie, "username=");
            if (username) {
                username += 8; // skip "username="
                char *end = strchr(username, ';');
                if (end) {
                    *end = '\0';
                }
                show_secret_page(username);
            } else {
                printf("Location: /login\r\n\r\n");
                printf("<html><head><meta http-equiv='refresh' content='0;url=/login'></head><body></body></html>");
            }
        } else {
            show_index_page();
        }
    } else if (strcmp(request_method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char *data = malloc(content_length + 1);
        fread(data, 1, content_length, stdin);
        data[content_length] = '\0';

        const char *username = strstr(data, "username=");
        const char *password = strstr(data, "password=");

        if (username && password) {
            username += 9; // skip "username="
            password += 9; // skip "password="
            char *amp = strchr(username, '&');
            if (amp) {
                *amp = '\0';
            }
            amp = strchr(password, '&');
            if (amp) {
                *amp = '\0';
            }
            do_login(username, password);
        } else {
            printf("Content-Type: text/html\r\n\r\n");
            printf("<html><body>Login Failed. <a href=\"/login\">Try again</a></body></html>");
        }

        free(data);
    }

    return 0;
}