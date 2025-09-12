#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Set-Cookie: username=%s; HttpOnly\n", username);
        printf("Location: /secret.html\n\n");
        return 1;
    }
    return 0;
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Login</h2>");
    printf("<form action=\"/do_login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(void) {
    char request_method[10];
    char content_length_str[10];
    int content_length;
    char *username = malloc(MAX_USERNAME_LENGTH + 1);
    char *password = malloc(MAX_PASSWORD_LENGTH + 1);

    strcpy(request_method, getenv("REQUEST_METHOD"));
    if (strcmp(request_method, "POST") == 0) {
        content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 20) {
            printf("Content-Type: text/plain\n\n");
            printf("Invalid request length\n");
            free(username);
            free(password);
            return 1;
        }
        fgets(username, MAX_USERNAME_LENGTH, stdin);
        fgets(password, MAX_PASSWORD_LENGTH, stdin);

        // Simple parsing of input assuming format: username=admin&password=password123
        char *username_start = strchr(username, '=') + 1;
        char *username_end = strchr(username_start, '&');
        *username_end = '\0';
        char *password_start = strchr(password, '=') + 1;
        password_start[strcspn(password_start, "&")] = '\0';

        if (do_login(username_start, password_start)) {
            free(username);
            free(password);
            return 0;
        }
    }

    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Login Failed</h2>");
    printf("<a href=\"/login.html\">Try again</a>");
    printf("</body></html>");

    free(username);
    free(password);
    return 1;
}