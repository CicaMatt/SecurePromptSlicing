#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("Set-Cookie: username=%s; path=/\n", username);
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
    printf("<form action=\"/do_login\" method=\"post\">");
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
    char content_length_str[32];
    int content_length;
    char* post_data = NULL;

    strcpy(request_method, getenv("REQUEST_METHOD"));

    if (strcmp(request_method, "GET") == 0) {
        char* query_string = getenv("QUERY_STRING");
        if (query_string && strcmp(query_string, "/login.html") == 0) {
            login_form();
        } else if (query_string && strcmp(query_string, "/secret.html") == 0) {
            secret_page();
        } else {
            index_page();
        }
    } else if (strcmp(request_method, "POST") == 0) {
        content_length = atoi(getenv("CONTENT_LENGTH"));
        post_data = malloc(content_length + 1);
        fread(post_data, 1, content_length, stdin);
        post_data[content_length] = '\0';

        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];

        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        if (do_login(username, password)) {
            // Redirect handled in do_login
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<h1>Login Failed</h1>");
            printf("<a href=\"/login.html\">Try again</a>");
            printf("</body></html>");
        }

        free(post_data);
    }

    return 0;
}