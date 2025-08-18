#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int check_credentials(const char* username, const char* password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Login</h2>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char* username, const char* password) {
    if (check_credentials(username, password)) {
        printf("Set-Cookie: session=valid; Path=/\n");
        printf("Location: /secret\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h2>Login Failed</h2>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void secret_page(const char* session) {
    if (session != NULL && strcmp(session, "valid") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        printf("Location: /login\n");
    }
}

int main() {
    char* request_method = getenv("REQUEST_METHOD");
    char* query_string = getenv("QUERY_STRING");
    char* http_cookie = getenv("HTTP_COOKIE");

    if (request_method == NULL) {
        index_page();
        return 0;
    }

    if (strcmp(request_method, "GET") == 0) {
        if (strstr(query_string, "login")) {
            login_page();
        } else if (strstr(query_string, "secret")) {
            secret_page(http_cookie);
        } else {
            index_page();
        }
    } else if (strcmp(request_method, "POST") == 0) {
        char username[MAX_USERNAME];
        char password[MAX_PASSWORD];
        
        scanf("username=%[^&]&password=%s", username, password);

        do_login(username, password);
    }

    return 0;
}