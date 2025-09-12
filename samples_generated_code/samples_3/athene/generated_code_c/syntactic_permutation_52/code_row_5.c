#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

Session session;

void print_header() {
    printf("Content-Type: text/html\n\n");
}

void index_page() {
    print_header();
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<p><a href=\"/login\">Login</a></p>");
    printf("</body></html>");
}

void login_page() {
    print_header();
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(session.username, username, MAX_USERNAME_LEN);
        printf("Set-Cookie: session=%s\n", session.username);
        printf("Location: /secret\n");
    } else {
        login_page();
    }
}

void secret_page() {
    print_header();
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    const char *query_string = getenv("QUERY_STRING");

    if (strcmp(request_method, "GET") == 0) {
        if (query_string && strcmp(query_string, "page=login") == 0) {
            login_page();
        } else if (query_string && strcmp(query_string, "page=secret") == 0) {
            secret_page();
        } else {
            index_page();
        }
    } else if (strcmp(request_method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        fread(buffer, 1, content_length, stdin);
        buffer[content_length] = '\0';

        char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN];
        sscanf(buffer, "username=%[^&]&password=%s", username, password);

        do_login(username, password);
    }

    return 0;
}