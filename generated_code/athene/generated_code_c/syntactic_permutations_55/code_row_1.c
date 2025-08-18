#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login() {
    char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "POST") == 0) {
        char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = atoi(content_length_str);
        char *data = malloc(content_length + 1);
        fread(data, 1, content_length, stdin);
        data[content_length] = '\0';

        char username[256], password[256];
        sscanf(data, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            printf("Content-Type: text/html\r\n");
            printf("Location: /admin_page\r\n\r\n");
        } else {
            printf("Content-Type: text/html\r\n");
            printf("Location: /login?error=1\r\n\r\n");
        }

        free(data);
    }
}

void index() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void user_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Page</h1>");
    printf("<p>Welcome, User!</p>");
    printf("<a href=\"/\">Home</a>");
    printf("</body></html>");
}

void admin_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Admin Page</h1>");
    printf("<p>Welcome, Admin!</p>");
    printf("<a href=\"/\">Home</a>");
    printf("</body></html>");
}