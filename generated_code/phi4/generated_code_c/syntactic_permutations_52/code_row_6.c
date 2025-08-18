#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

void set_session(Session *session, const char *username) {
    strncpy(session->username, username, sizeof(session->username) - 1);
    session->username[sizeof(session->username) - 1] = '\0';
}

int is_authenticated(const char *input_username, const char *input_password) {
    return strcmp(input_username, "admin") == 0 && strcmp(input_password, "password123") == 0;
}

void do_login(Session *session, const char *username, const char *password) {
    if (is_authenticated(username, password)) {
        set_session(session, username);
        printf("Redirecting to secret page...\n");
        print_secret_page();
    } else {
        printf("Invalid credentials. Please try again.\n");
        print_index_page();
    }
}

void print_login_page() {
    printf("Login Page\n");
    printf("Username: ");
    char username[MAX_USERNAME_LENGTH];
    scanf("%49s", username);
    printf("Password: ");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%49s", password);

    Session session = {0};
    do_login(&session, username, password);
}

void print_index_page() {
    printf("Index Page\n");
    printf("Click here to [login](#).\n");
}

void print_secret_page() {
    printf("Secret Page: Secret settings\n");
}

int main() {
    print_index_page();
    return 0;
}