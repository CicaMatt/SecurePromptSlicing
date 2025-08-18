#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

char *session_username = NULL;

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        session_username = malloc(strlen(username) + 1);
        strcpy(session_username, username);
        return 1;
    }
    return 0;
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form action=\"/do_login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page() {
    if (session_username) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        printf("Status: 403 Forbidden\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Access Denied</h1>");
        printf("</body></html>");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");

    if (method == NULL) {
        index_page();
    } else if (strcmp(method, "GET") == 0) {
        const char *query_string = getenv("QUERY_STRING");
        if (query_string && strcmp(query_string, "page=login") == 0) {
            login_page();
        } else if (query_string && strcmp(query_string, "page=secret") == 0) {
            secret_page();
        } else {
            index_page();
        }
    } else if (strcmp(method, "POST") == 0) {
        char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = content_length_str ? atoi(content_length_str) : 0;
        char post_data[1024];
        if (content_length > 0 && content_length < sizeof(post_data)) {
            fread(post_data, 1, content_length, stdin);
            post_data[content_length] = '\0';
            char username[MAX_USERNAME_LENGTH + 1], password[MAX_PASSWORD_LENGTH + 1];
            sscanf(post_data, "username=%[^&]&password=%s", username, password);
            if (do_login(username, password)) {
                printf("Location: /secret_page.cgi?page=secret\n\n");
            } else {
                printf("Content-Type: text/html\n\n");
                printf("<html><body>");
                printf("<h1>Login Failed</h1>");
                printf("<a href=\"/login.html\">Try again</a>");
                printf("</body></html>");
            }
        }
    }

    if (session_username) {
        free(session_username);
        session_username = NULL;
    }

    return 0;
}