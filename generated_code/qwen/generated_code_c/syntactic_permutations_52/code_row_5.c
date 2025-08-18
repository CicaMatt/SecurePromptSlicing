#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

Session session;

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(session.username, username, MAX_USERNAME_LENGTH);
        printf("Location: secret.html\r\n\r\n");
    } else {
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
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

void secret_page() {
    if (strlen(session.username) > 0) {
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        printf("Location: index.html\r\n\r\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        index_page();
    } else if (strcmp(argv[1], "login") == 0) {
        if (argc != 4) {
            printf("<html><body>");
            printf("<h1>Invalid request</h1>");
            printf("</body></html>");
        } else {
            do_login(argv[2], argv[3]);
        }
    } else if (strcmp(argv[1], "secret") == 0) {
        secret_page();
    } else {
        index_page();
    }
    return 0;
}