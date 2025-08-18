#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method=\"post\" action=\"/cgi-bin/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char *data = getenv("CONTENT_LENGTH");
    int length = 0;
    if (data != NULL) {
        length = atoi(data);
    }

    char buffer[length + 1];
    if (fread(buffer, 1, length, stdin) == length) {
        buffer[length] = '\0';

        char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
        sscanf(buffer, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            printf("Location: /cgi-bin/admin_page\n\n");
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("Invalid username or password.");
            printf("</body></html>");
        }
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        do_login();
    }

    return 0;
}