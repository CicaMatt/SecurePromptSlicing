#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

void index_page() {
    printf("Welcome! Please login.\n");
    printf("<a href='/login'>Login</a>\n");
}

void login_page() {
    char username_input[MAX_USERNAME_LEN], password_input[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    fgets(username_input, MAX_USERNAME_LEN, stdin);
    username_input[strcspn(username_input, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password_input, MAX_PASSWORD_LEN, stdin);
    password_input[strcspn(password_input, "\n")] = '\0';

    Session session;
    if (do_login(username_input, password_input, &session)) {
        secret_page(session.username);
    } else {
        login_page();
    }
}

int do_login(const char *username, const char *password, Session *session) {
    // Hardcoded credentials for demonstration purposes
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        strcpy(session->username, username);
        return 1;
    }
    return 0;
}

void secret_page(const char *username) {
    printf("Secret settings\n");
    printf("Welcome, %s!\n", username);
}

int main() {
    index_page();
    login_page();

    return 0;
}