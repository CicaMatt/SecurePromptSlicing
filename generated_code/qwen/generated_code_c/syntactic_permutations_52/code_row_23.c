#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

int do_login(const char *username, const char *password, Session *session) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strcpy(session->username, username);
        return 1;
    }
    return 0;
}

void show_login_page() {
    printf("Login Page\n");
    printf("Username: <input type=\"text\" name=\"username\">\n");
    printf("Password: <input type=\"password\" name=\"password\">\n");
    printf("<button type=\"submit\">Login</button>\n");
    printf("<a href=\"/login.html\">Go to Login Page</a>\n");
}

void show_secret_page() {
    printf("Secret settings\n");
}

int main() {
    Session session;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (do_login(username, password, &session)) {
        show_secret_page();
    } else {
        show_login_page();
    }

    return 0;
}