#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
} Session;

void do_login(Session *session, const char *username, const char *password) {
    if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
        strcpy(session->username, username);
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid credentials.\n");
        show_index_page();
    }
}

void show_index_page() {
    printf("Index Page\n");
    printf("<a href='/login'>Login</a>\n");
}

void show_login_page() {
    printf("Login Page\n");
    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    do_login(NULL, username, password);
}

void show_secret_page() {
    Session session = {"user"};
    if (strcmp(session.username, "user") == 0) {
        printf("Secret Page\n");
        printf("Hello, %s! Welcome to the secret page.\n", session.username);
    } else {
        printf("Access Denied. Redirecting to login...\n");
        show_login_page();
    }
}

int main() {
    show_index_page();
    return 0;
}