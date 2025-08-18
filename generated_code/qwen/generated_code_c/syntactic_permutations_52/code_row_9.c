#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

void print_login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form>");
    printf("</body></html>");
}

void print_index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<a href=\"login.cgi\">Login</a>");
    printf("</body></html>");
}

void print_secret_page(const char* username) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("<p>Welcome, %s!</p>", username);
    printf("</body></html>");
}

int main() {
    char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        fgets(buffer, content_length + 1, stdin);
        
        char username[32], password[32];
        sscanf(buffer, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            printf("Set-Cookie: username=%s; path=/\n", username);
            print_secret_page(username);
        } else {
            print_login_page();
        }
    } else {
        char *cookie = getenv("HTTP_COOKIE");
        if (cookie && strstr(cookie, "username=")) {
            print_secret_page(strstr(cookie, "username=") + strlen("username="));
        } else {
            print_index_page();
        }
    }

    return 0;
}