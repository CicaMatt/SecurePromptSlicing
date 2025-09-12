#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

void do_login(Session *session, const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(session->username, username, MAX_USERNAME_LENGTH);
        printf("Location: secret.html\r\n\r\n");
    } else {
        printf("<html><body>");
        printf("<h2>Login Failed</h2>");
        printf("<p>Incorrect username or password.</p>");
        printf("<a href=\"index.html\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"login.html\">Login</a>");
    printf("</body></html>");
}

void secret_page(Session *session) {
    if (strlen(session->username) > 0) {
        printf("<html><body>");
        printf("<h2>Secret settings</h2>");
        printf("</body></html>");
    } else {
        printf("Location: index.html\r\n\r\n");
    }
}

int main() {
    Session session = {""};
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];

        printf("Content-Type: text/html\r\n\r\n");

        scanf("username=%[^&]&password=%s", username, password);
        do_login(&session, username, password);
    } else if (request_method != NULL && strcmp(request_method, "GET") == 0) {
        char *path = getenv("PATH_INFO");
        printf("Content-Type: text/html\r\n\r\n");

        if (path != NULL) {
            if (strcmp(path, "/login.html") == 0) {
                printf("<html><body>");
                printf("<h1>Login</h1>");
                printf("<form method=\"post\" action=\"/cgi-bin/login.cgi\">");
                printf("Username: <input type=\"text\" name=\"username\"><br>");
                printf("Password: <input type=\"password\" name=\"password\"><br>");
                printf("<input type=\"submit\" value=\"Login\">");
                printf("</form>");
                printf("</body></html>");
            } else if (strcmp(path, "/secret.html") == 0) {
                secret_page(&session);
            } else {
                index_page();
            }
        } else {
            index_page();
        }
    }

    return 0;
}