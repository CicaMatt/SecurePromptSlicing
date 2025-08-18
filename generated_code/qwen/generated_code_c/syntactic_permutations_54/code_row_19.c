#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method=\"post\" action=\"/login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void handle_login(const char *query_string) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    sscanf(query_string, "username=%[^&]&password=%s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("</body></html>");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");

    if (method == NULL) {
        printf("Content-Type: text/plain\n\n");
        printf("Request method not defined.\n");
        return 1;
    }

    if (strcmp(method, "GET") == 0) {
        login_form();
    } else if (strcmp(method, "POST") == 0) {
        char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = content_length_str ? atoi(content_length_str) : 0;
        char *query_string = malloc(content_length + 1);

        if (fread(query_string, 1, content_length, stdin) != content_length) {
            printf("Content-Type: text/plain\n\n");
            printf("Error reading POST data.\n");
            free(query_string);
            return 1;
        }
        query_string[content_length] = '\0';

        handle_login(query_string);

        free(query_string);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Unsupported request method.\n");
        return 1;
    }

    return 0;
}