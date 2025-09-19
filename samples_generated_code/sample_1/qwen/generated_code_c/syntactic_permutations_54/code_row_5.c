#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void get_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char *data = getenv("CONTENT_LENGTH");
    int length = data ? atoi(data) : 0;
    if (length > 0) {
        char buffer[1024];
        fread(buffer, 1, length, stdin);
        buffer[length] = '\0';

        char username[MAX_USERNAME], password[MAX_PASSWORD];
        sscanf(buffer, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            printf("Location: /admin_page\n\n");
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<p>Invalid username or password</p>");
            printf("</body></html>");
        }
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (strcmp(request_method, "GET") == 0) {
        get_form();
    } else if (strcmp(request_method, "POST") == 0) {
        do_login();
    }
    return 0;
}