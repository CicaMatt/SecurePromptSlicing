#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char *username;
} Session;

Session session = {NULL};

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        session.username = strdup(username);
        printf("Location: /secret\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Redirecting to secret page...</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. Try again.</body></html>");
    }
}

void index() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void secret() {
    if (session.username != NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: /index\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are not logged in.</body></html>");
    }
}

int main(int argc, char **argv) {
    const char *path_info = getenv("PATH_INFO");
    if (strcmp(path_info, "/login") == 0) {
        char username[100], password[100];
        sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strcmp(path_info, "/index") == 0 || path_info == NULL) {
        index();
    } else if (strcmp(path_info, "/secret") == 0) {
        secret();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>404 Not Found</body></html>");
    }
    return 0;
}