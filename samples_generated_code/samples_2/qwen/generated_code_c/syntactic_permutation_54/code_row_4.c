#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

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

void do_login(const char *query_string) {
    char username[MAX_USERNAME_LENGTH] = {0};
    char password[MAX_PASSWORD_LENGTH] = {0};

    sscanf(query_string, "username=%[^&]&password=%s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Login failed. Please try again.</p>");
        printf("</body></html>");
    }
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    const char *query_string = getenv("QUERY_STRING");

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        char buffer[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 12] = {0};
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(buffer, sizeof(char), content_length, stdin);
        do_login(buffer);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Unsupported request method.</p>");
        printf("</body></html>");
    }

    return 0;
}