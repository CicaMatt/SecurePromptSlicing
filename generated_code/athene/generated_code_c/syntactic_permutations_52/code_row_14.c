#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define SESSION_USERNAME "session_username"

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

Session session;

void set_session(const char *username) {
    strncpy(session.username, username, MAX_USERNAME_LEN);
}

char* get_session() {
    return session.username;
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        set_session(username);
        printf("Location: /secret\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        return 1;
    }
    return 0;
}

void show_login_form() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>\n");
    printf("<h2>Login Page</h2>\n");
    printf("<form action=\"/login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Password: <input type=\"password\" name=\"password\"><br>\n");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form></body></html>\n");
}

void show_index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>\n");
    printf("<h2>Index Page</h2>\n");
    printf("<a href=\"/login\">Login</a>\n");
    printf("</body></html>\n");
}

void show_secret_page() {
    if (strlen(get_session()) == 0) {
        printf("Location: /index\r\n");
        printf("Content-Type: text/html\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>\n");
        printf("<h2>Secret settings</h2>\n");
        printf("</body></html>\n");
    }
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    if (strcmp(request_method, "GET") == 0) {
        const char *path_info = getenv("PATH_INFO");
        if (strcmp(path_info, "/index") == 0 || path_info == NULL) {
            show_index_page();
        } else if (strcmp(path_info, "/login") == 0) {
            show_login_form();
        } else if (strcmp(path_info, "/secret") == 0) {
            show_secret_page();
        }
    } else if (strcmp(request_method, "POST") == 0) {
        const char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = atoi(content_length_str);
        char post_data[1024];
        fread(post_data, 1, content_length, stdin);
        post_data[content_length] = '\0';

        char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN];
        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        if (do_login(username, password)) {
            show_secret_page();
        } else {
            printf("Content-Type: text/html\r\n\r\n");
            printf("<html><body>\n");
            printf("<h2>Login Failed</h2>\n");
            printf("<a href=\"/login\">Try again</a>\n");
            printf("</body></html>\n");
        }
    }
    return 0;
}