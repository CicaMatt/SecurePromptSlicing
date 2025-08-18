#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

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

void do_login(char *post_data) {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    sscanf(post_data, "username=%[^&]&password=%s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("</body></html>");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");

    if (method == NULL) {
        return 1;
    }

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char *post_data = malloc(content_length + 1);
        fread(post_data, 1, content_length, stdin);
        post_data[content_length] = '\0';
        do_login(post_data);
        free(post_data);
    }

    return 0;
}