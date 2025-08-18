#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
} Session;

Session session;

int check_credentials(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void do_login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        strncpy(session.username, username, MAX_USERNAME - 1);
        printf("Location: secret.html\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<p>Invalid username or password. <a href=\"index.html\">Try again</a>.</p>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the homepage</h1>");
    printf("<p>Please <a href=\"login.html\">log in</a> to access secret settings.</p>");
    printf("</body></html>");
}

void login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h2>Login</h2>");
    printf("<form action=\"do_login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page() {
    if (session.username[0] != '\0') {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("<p>Welcome, %s!</p>", session.username);
        printf("</body></html>");
    } else {
        printf("Location: index.html\r\n\r\n");
    }
}

int main() {
    char request_method[10];
    char content_length_str[10];
    int content_length = 0;
    char *post_data;

    strcpy(session.username, "");

    getenv_s(&content_length, content_length_str, sizeof(content_length_str), "CONTENT_LENGTH");

    if (getenv_s(NULL, request_method, sizeof(request_method), "REQUEST_METHOD") == 0) {
        if (strcmp(request_method, "POST") == 0 && content_length > 0) {
            post_data = malloc(content_length + 1);
            if (post_data != NULL) {
                fread(post_data, 1, content_length, stdin);
                post_data[content_length] = '\0';

                char username[MAX_USERNAME];
                char password[MAX_PASSWORD];

                sscanf(post_data, "username=%[^&]&password=%s", username, password);

                do_login(username, password);
                free(post_data);
            }
        } else if (strcmp(request_method, "GET") == 0) {
            const char *path = getenv("PATH_INFO");
            if (path != NULL) {
                if (strstr(path, "/login.html")) {
                    login_page();
                } else if (strstr(path, "/secret.html")) {
                    secret_page();
                }
            } else {
                index_page();
            }
        } else {
            index_page();
        }
    }

    return 0;
}