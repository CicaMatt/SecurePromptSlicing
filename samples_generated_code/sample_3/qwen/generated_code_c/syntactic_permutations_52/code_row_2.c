#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: session=active; path=/\r\n");
        printf("Location: /secret\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login\">Login</a>");
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

    if (request_method == NULL || strcmp(request_method, "GET") != 0) {
        index_page();
        return 1;
    }

    if (query_string != NULL && strstr(query_string, "login")) {
        const char* username = getenv("HTTP_COOKIE");
        const char* password = getenv("HTTP_COOKIE");

        // Simplified for demonstration; in practice parse query string properly
        if (username == NULL || password == NULL) {
            printf("Content-Type: text/html\r\n\r\n");
            printf("<html><body>");
            printf("<h1>Login</h1>");
            printf("<form method=\"get\" action=\"/login\">");
            printf("Username: <input type=\"text\" name=\"username\"><br>");
            printf("Password: <input type=\"password\" name=\"password\"><br>");
            printf("<input type=\"submit\" value=\"Submit\">");
            printf("</form>");
            printf("</body></html>");
        } else {
            do_login(username, password);
        }
    } else if (query_string != NULL && strstr(query_string, "secret")) {
        secret_page();
    } else {
        index_page();
    }

    return 0;
}