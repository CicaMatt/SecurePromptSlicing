#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
} Session;

Session current_session = {"guest"};

int do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(current_session.username, username, MAX_USERNAME);
        return 1;
    }
    return 0;
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_page(const char* username, const char* password) {
    if (do_login(username, password)) {
        printf("Location: /secret.html\r\n");
        printf("\r\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<a href=\"/login.html\">Try again</a>");
        printf("</body></html>");
    }
}

void secret_page() {
    if (strcmp(current_session.username, "admin") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Secret Settings</h1>");
        printf("</body></html>");
    } else {
        printf("Location: /login.html\r\n");
        printf("\r\n");
    }
}

int main() {
    char* request_method = getenv("REQUEST_METHOD");
    if (request_method != NULL && strcmp(request_method, "GET") == 0) {
        index_page();
    } else if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        char username[MAX_USERNAME];
        char password[MAX_PASSWORD];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            char buffer[512];
            fread(buffer, 1, content_length, stdin);
            sscanf(buffer, "username=%[^&]&password=%s", username, password);
            login_page(username, password);
        } else {
            index_page();
        }
    } else if (strcmp(request_method, "SECRET") == 0) {
        secret_page();
    } else {
        index_page();
    }
    return 0;
}