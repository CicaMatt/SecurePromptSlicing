#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password"

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        login();
    }
}

int main() {
    char request_method[10];
    char content_length_str[32];
    int content_length;
    char* post_data = NULL;

    strcpy(request_method, getenv("REQUEST_METHOD"));

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        content_length = atoi(getenv("CONTENT_LENGTH"));
        post_data = malloc(content_length + 1);
        fread(post_data, 1, content_length, stdin);
        post_data[content_length] = '\0';

        char username[MAX_USERNAME];
        char password[MAX_PASSWORD];
        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        do_login(username, password);

        free(post_data);
    }

    return 0;
}