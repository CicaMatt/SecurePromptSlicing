#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
} Session;

Session current_session = {""};

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        strncpy(current_session.username, username, MAX_USERNAME);
        printf("Location: /secret.html\r\n\r\n");
    } else {
        printf("<html><body>Login Failed. <a href=\"/index.html\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("<html><body>Welcome! <a href=\"/login.html\">Login</a></body></html>");
}

void secret_page() {
    if (strlen(current_session.username) > 0) {
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: /index.html\r\n\r\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    if (strcmp(argv[1], "/login") == 0 && argv[2] != NULL && argv[3] != NULL) {
        do_login(argv[2], argv[3]);
    } else if (strcmp(argv[1], "/index.html") == 0) {
        index_page();
    } else if (strcmp(argv[1], "/secret.html") == 0) {
        secret_page();
    } else {
        printf("<html><body>404 Not Found</body></html>");
    }

    return 0;
}