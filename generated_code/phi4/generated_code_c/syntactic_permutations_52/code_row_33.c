#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

void set_session_username(Session *session, const char* username) {
    strncpy(session->username, username, MAX_USERNAME_LENGTH);
}

int do_login(const char* input_username, const char* input_password, Session *session) {
    if (strcmp(input_username, "admin") == 0 && strcmp(input_password, "password123") == 0) {
        set_session_username(session, input_username);
        return 1; // Login successful
    }
    return 0; // Login failed
}

void show_secret_page(Session *session) {
    if (strlen(session->username) > 0) {
        printf("Secret settings\n");
    } else {
        printf("Access denied. Please log in.\n");
    }
}

void index_page() {
    printf("Welcome to the homepage!\n");
    printf("Please login: <a href='login'>Login</a>\n");
}

void login_page(Session *session) {
    char username[MAX_USERNAME_LENGTH];
    char password[50];

    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (do_login(username, password, session)) {
        show_secret_page(session);
    } else {
        printf("Invalid credentials. Please try again.\n");
    }
}

int main() {
    Session session = {0};

    char choice;
    do {
        printf("\n1: Index Page\n2: Login Page\n3: Exit\nChoose an option: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                index_page();
                break;
            case '2':
                login_page(&session);
                break;
            case '3':
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '3');

    return 0;
}