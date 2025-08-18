#include <stdio.h>
#include <string.h>

#define SESSION_KEY 1

typedef struct {
    char username[100];
} Session;

Session session = {0};

void set_session_username(const char *username) {
    strncpy(session.username, username, sizeof(session.username) - 1);
}

int is_logged_in() {
    return strlen(session.username) > 0;
}

void redirect_to_secret_page() {
    printf("Redirecting to the secret page...\n");
    show_secret_page();
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "correct_user") == 0 && strcmp(password, "correct_pass") == 0) {
        set_session_username(username);
        redirect_to_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void show_index_page() {
    printf("Welcome to the index page.\n");
    printf("<a href=\"/login\">Login</a>\n");
}

void show_login_page() {
    printf("Login Page:\n");
    printf("Username: ");
    char username[100];
    scanf("%s", username);
    
    printf("Password: ");
    char password[100];
    scanf("%s", password);

    do_login(username, password);
}

void show_secret_page() {
    if (is_logged_in()) {
        printf("Secret settings\n");
    } else {
        printf("You must be logged in to view this page.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "login") == 0) {
        show_login_page();
    } else if (argc > 1 && strcmp(argv[1], "secret") == 0) {
        show_secret_page();
    } else {
        show_index_page();
    }
    return 0;
}