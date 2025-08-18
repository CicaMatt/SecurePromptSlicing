#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

Session current_session = {""};

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(current_session.username, username, MAX_USERNAME_LENGTH);
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
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page() {
    if (strlen(current_session.username) > 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        printf("Status: 403 Forbidden\n\n");
        printf("Access Denied");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        index_page();
    } else if (strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME_LENGTH] = "";
        char password[MAX_PASSWORD_LENGTH] = "";

        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            char *input = malloc(content_length + 1);
            fread(input, content_length, 1, stdin);
            input[content_length] = '\0';

            sscanf(input, "username=%[^&]&password=%s", username, password);

            free(input);

            if (do_login(username, password)) {
                printf("Location: /secret_page.cgi\n\n");
            } else {
                printf("Content-Type: text/html\n\n");
                printf("<html><body>");
                printf("<h1>Login Failed</h1>");
                printf("<a href=\"/login.html\">Try again</a>");
                printf("</body></html>");
            }
        }
    } else if (strcmp(getenv("SCRIPT_NAME"), "/secret_page.cgi") == 0) {
        secret_page();
    }

    return 0;
}