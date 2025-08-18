#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

Session current_session;

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(current_session.username, username, MAX_USERNAME_LEN);
        printf("Location: /secret.html\r\n\r\n");
    } else {
        printf("<html><body>Invalid username or password. <a href=\"/login.html\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("<html><body>Welcome! <a href=\"/login.html\">Login here</a></body></html>");
}

void secret_page() {
    if (strlen(current_session.username) > 0) {
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: /login.html\r\n\r\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;

    if (strcmp(argv[1], "/") == 0 || strcmp(argv[1], "/index.html") == 0) {
        index_page();
    } else if (strcmp(argv[1], "/login.html") == 0) {
        if (argc > 3 && strcmp(argv[2], "POST") == 0) {
            do_login(argv[3], argv[4]);
        } else {
            printf("<html><body><form action=\"/login.html\" method=\"post\">Username: <input type=\"text\" name=\"username\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>");
        }
    } else if (strcmp(argv[1], "/secret.html") == 0) {
        secret_page();
    }

    return 0;
}