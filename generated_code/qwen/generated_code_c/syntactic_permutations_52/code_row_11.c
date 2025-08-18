#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("Content-type: text/html\r\n");
        printf("Set-Cookie: username=admin; HttpOnly\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<p>Redirecting to secret page...</p>");
        printf("<script>window.location.href='/secret';</script>");
        printf("</body></html>");
    } else {
        printf("Content-type: text/html\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Index Page</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");

    if (strcmp(request_method, "GET") == 0) {
        if (strstr(query_string, "/login")) {
            printf("Content-type: text/html\r\n");
            printf("\r\n");
            printf("<html><body>");
            printf("<h1>Login Page</h1>");
            printf("<form action=\"/do_login\" method=\"post\">");
            printf("Username: <input type=\"text\" name=\"username\"><br>");
            printf("Password: <input type=\"password\" name=\"password\"><br>");
            printf("<input type=\"submit\" value=\"Login\">");
            printf("</form>");
            printf("</body></html>");
        } else if (strstr(query_string, "/do_login")) {
            char username[MAX_USERNAME];
            char password[MAX_PASSWORD];
            sscanf(query_string, "username=%[^&]&password=%s", username, password);
            do_login(username, password);
        } else if (strstr(query_string, "/secret")) {
            secret_page();
        } else {
            index_page();
        }
    }

    return 0;
}