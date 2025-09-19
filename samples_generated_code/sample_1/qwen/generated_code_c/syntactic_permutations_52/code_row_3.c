#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: username=%s; path=/\r\n", username);
        printf("Location: /secret\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<p>Invalid username or password. <a href=\"/login\">Try again</a></p>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<p>Click <a href=\"/login\">here</a> to log in.</p>");
    printf("</body></html>");
}

void login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(void) {
    char* request_uri = getenv("REQUEST_URI");
    char* request_method = getenv("REQUEST_METHOD");

    if (request_uri == NULL || strcmp(request_uri, "/") == 0) {
        index_page();
    } else if (strcmp(request_uri, "/login") == 0) {
        login_page();
    } else if (strcmp(request_uri, "/do_login") == 0 && strcmp(request_method, "POST") == 0) {
        char username[100], password[100];
        scanf("username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strcmp(request_uri, "/secret") == 0) {
        secret_page();
    } else {
        printf("Status: 404 Not Found\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Not Found</h1>");
        printf("</body></html>");
    }

    return 0;
}