#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_page(const char *username, const char *password) {
    if (do_login(username, password)) {
        printf("Set-Cookie: username=%s; path=/\n", username);
        printf("Location: /secret.html\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<a href=\"/login.html\">Try again</a>");
        printf("</body></html>");
    }
}

void secret_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");

    if (strcmp(request_method, "GET") == 0) {
        index_page();
    } else if (strcmp(request_method, "POST") == 0) {
        char username[MAX_USERNAME];
        char password[MAX_PASSWORD];
        scanf("%s %*c %s", username, password);
        login_page(username, password);
    } else if (query_string != NULL && strcmp(query_string, "secret") == 0) {
        secret_page();
    }

    return 0;
}