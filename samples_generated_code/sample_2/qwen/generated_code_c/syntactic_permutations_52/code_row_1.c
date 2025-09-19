#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char *username;
} Session;

void do_login(Session *session, const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        session->username = strdup(username);
        printf("Location: /secret\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page(Session *session) {
    if (session->username) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        printf("Location: /login\n\n");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");
    Session session = {0};

    if (strcmp(method, "GET") == 0) {
        if (strstr(query_string, "/login")) {
            login_page();
        } else if (strstr(query_string, "/secret")) {
            secret_page(&session);
        } else {
            index_page();
        }
    } else if (strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];
        scanf("username=%[^&]&password=%s", username, password);
        do_login(&session, username, password);
    }

    return 0;
}