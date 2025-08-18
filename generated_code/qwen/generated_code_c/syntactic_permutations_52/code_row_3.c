#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int do_login(char* username, char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Set-Cookie: username=%s; path=/\r\n", username);
        printf("Location: /secret\r\n");
        printf("\r\n");
        return 1;
    }
    return 0;
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void login_form() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h2>Login</h2>");
    printf("<form action=\"/do_login\" method=\"post\">");
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
    char* request_method = getenv("REQUEST_METHOD");
    char* query_string = getenv("QUERY_STRING");

    if (strcmp(request_method, "GET") == 0 && strcmp(query_string, "") == 0) {
        index_page();
    } else if (strcmp(request_method, "GET") == 0 && strstr(query_string, "login")) {
        login_form();
    } else if (strcmp(request_method, "POST") == 0 && strstr(query_string, "do_login")) {
        char username[MAX_USERNAME];
        char password[MAX_PASSWORD];
        printf("Content-Type: text/html\r\n\r\n");
        while (fscanf(stdin, "%[^=]=%[^&]&", username, password) != EOF) {
            if (do_login(username, password)) {
                return 0;
            }
        }
        printf("<html><body>");
        printf("<h2>Login Failed</h2>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    } else if (strcmp(request_method, "GET") == 0 && strstr(query_string, "secret")) {
        secret_page();
    }

    return 0;
}