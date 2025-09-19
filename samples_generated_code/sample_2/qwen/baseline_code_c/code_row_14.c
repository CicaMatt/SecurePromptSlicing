#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

char session_username[MAX_USERNAME_LEN] = "";

int do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        strncpy(session_username, username, MAX_USERNAME_LEN);
        return 1;
    }
    return 0;
}

void show_index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the homepage</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void show_login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form action=\"do_login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void show_secret_page() {
    if (strlen(session_username) > 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        printf("Status: 302 Found\r\n");
        printf("Location: /login.html\r\n\r\n");
    }
}

int main() {
    char* request_method = getenv("REQUEST_METHOD");

    if (request_method == NULL || strcmp(request_method, "GET") == 0) {
        show_index_page();
    } else if (strcmp(request_method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char* post_data = malloc(content_length + 1);
        fread(post_data, content_length, 1, stdin);
        post_data[content_length] = '\0';

        char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN];
        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        if (do_login(username, password)) {
            printf("Status: 302 Found\r\n");
            printf("Location: /secret.cgi\r\n\r\n");
        } else {
            show_login_page();
        }

        free(post_data);
    }

    return 0;
}