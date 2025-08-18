#include <stdio.h>
#include <string.h>

void print_header() {
    printf("Content-Type: text/html\n\n");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        print_header();
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        print_header();
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p><a href=\"/login\">Try again</a></p>");
        printf("</body></html>");
    }
}

void show_login_page() {
    print_header();
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "POST") == 0) {
        char username[100], password[100];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), content_length, stdin);
        sscanf(username, "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else {
        show_login_page();
    }
    return 0;
}