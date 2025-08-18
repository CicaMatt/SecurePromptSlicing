#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

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
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h2>Login Failed</h2>");
        printf("</body></html>");
    }
}

int main() {
    const char* method = getenv("REQUEST_METHOD");

    if (method == NULL) {
        return 1;
    }

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        char buffer[1024];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(buffer, 1, content_length, stdin);
        buffer[content_length] = '\0';

        // Simple parsing of form data
        const char* username_start = strstr(buffer, "username=") + strlen("username=");
        const char* password_start = strstr(buffer, "password=") + strlen("password=");
        char username[256], password[256];

        sscanf(username_start, "%[^&]", username);
        sscanf(password_start, "%s", password);

        do_login(username, password);
    }

    return 0;
}