#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char *username;
} Session;

Session session = {NULL};

void set_session(const char *username) {
    if (session.username != NULL) free(session.username);
    session.username = strdup(username);
}

void clear_session() {
    if (session.username != NULL) free(session.username);
    session.username = NULL;
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        set_session(username);
        return 1;
    }
    return 0;
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
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void secret_page() {
    if (session.username == NULL) {
        printf("Location: /login\n\n");
        return;
    }
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

void handle_request(const char *uri, const char *method, const char *username, const char *password) {
    if (strcmp(uri, "/") == 0 && strcmp(method, "GET") == 0) {
        index_page();
    } else if (strcmp(uri, "/login") == 0 && strcmp(method, "GET") == 0) {
        login_page();
    } else if (strcmp(uri, "/do_login") == 0 && strcmp(method, "POST") == 0) {
        if (do_login(username, password)) {
            printf("Location: /secret\n\n");
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<p>Login failed</p>");
            printf("<a href=\"/login\">Try again</a>");
            printf("</body></html>");
        }
    } else if (strcmp(uri, "/secret") == 0 && strcmp(method, "GET") == 0) {
        secret_page();
    } else {
        printf("Status: 404 Not Found\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Page not found</p>");
        printf("</body></html>");
    }
}

int main() {
    // Simulate a request for demonstration purposes
    handle_request("/", "GET", "", "");
    clear_session();
    return 0;
}