#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
} Session;

void start_session(Session *session, const char *username) {
    strncpy(session->username, username, MAX_USERNAME);
}

int do_login(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_page(Session *session, const char *username, const char *password) {
    if (do_login(username, password)) {
        start_session(session, username);
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

void secret_page(Session *session) {
    if (strlen(session->username) > 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        printf("Location: /login.html\r\n");
        printf("\r\n");
    }
}

int main() {
    Session session = {""};
    char *request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "GET") == 0) {
        index_page();
    } else if (strcmp(request_method, "POST") == 0) {
        char username[MAX_USERNAME];
        char password[MAX_PASSWORD];
        
        // Simulate reading POST data
        scanf("username=%[^&]&password=%s", username, password);
        
        login_page(&session, username, password);
    } else if (strcmp(request_method, "SECRET") == 0) { // Custom method to simulate secret page access
        secret_page(&session);
    }

    return 0;
}