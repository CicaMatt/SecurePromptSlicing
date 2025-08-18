#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Set-Cookie: session_username=%s; HttpOnly\n", username);
        printf("Location: /secret\nContent-Length: 0\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void show_login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void show_index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<p>Click <a href=\"/login\">here</a> to log in.</p>");
    printf("</body></html>");
}

void show_secret_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main() {
    char* request_method = getenv("REQUEST_METHOD");
    char* query_string = getenv("QUERY_STRING");
    
    if (strcmp(request_method, "GET") == 0) {
        if (query_string && strcmp(query_string, "/login") == 0) {
            show_login_page();
        } else if (query_string && strcmp(query_string, "/secret") == 0) {
            show_secret_page();
        } else {
            show_index_page();
        }
    } else if (strcmp(request_method, "POST") == 0) {
        if (query_string && strcmp(query_string, "/do_login") == 0) {
            char username[MAX_USERNAME_LEN];
            char password[MAX_PASSWORD_LEN];
            printf("Content-Type: text/html\n\n");
            scanf("username=%[^&]&password=%s", username, password);
            do_login(username, password);
        }
    }
    
    return 0;
}