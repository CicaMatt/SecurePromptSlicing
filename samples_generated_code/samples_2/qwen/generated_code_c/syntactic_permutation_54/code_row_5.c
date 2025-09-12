#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 20
#define MAX_PASSWORD 20

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid username or password</p>");
        printf("</body></html>");
    }
}

int main() {
    char request_method[10];
    char query_string[1024];
    char post_data[1024];

    strcpy(request_method, getenv("REQUEST_METHOD"));

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(post_data, content_length, 1, stdin);
        post_data[content_length] = '\0';

        char* username_start = strstr(post_data, "username=");
        char* password_start = strstr(post_data, "password=");

        if (username_start && password_start) {
            char username[MAX_USERNAME];
            char password[MAX_PASSWORD];

            sscanf(username_start + strlen("username="), "%[^&]", username);
            sscanf(password_start + strlen("password="), "%s", password);

            do_login(username, password);
        }
    }

    return 0;
}