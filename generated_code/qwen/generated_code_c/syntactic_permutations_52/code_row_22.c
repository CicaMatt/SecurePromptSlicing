#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

int do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1;
    }
    return 0;
}

void show_index_page() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Index Page</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>\r\n");
}

void show_login_page() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form action=\"/submit-login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>\r\n");
}

void show_secret_page(const char* username) {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Secret Settings</h1>");
    printf("Welcome, %s!", username);
    printf("</body></html>\r\n");
}

void handle_login_submission(const char* request_body) {
    const char* username = strstr(request_body, "username=");
    const char* password = strstr(request_body, "password=");

    if (username && password) {
        username += strlen("username=");
        password += strlen("password=");
        
        char user[MAX_USERNAME_LEN];
        char pass[MAX_PASSWORD_LEN];
        sscanf(username, "%[^&]", user);
        sscanf(password, "%s", pass);

        if (do_login(user, pass)) {
            show_secret_page(user);
            return;
        }
    }
    printf("HTTP/1.1 403 Forbidden\r\nContent-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Access Denied</h1>");
    printf("</body></html>\r\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        show_index_page();
    } else if (strcmp(argv[1], "/login") == 0) {
        show_login_page();
    } else if (strcmp(argv[1], "/submit-login") == 0 && argc > 2) {
        handle_login_submission(argv[2]);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Page Not Found</h1>");
        printf("</body></html>\r\n");
    }
    return 0;
}