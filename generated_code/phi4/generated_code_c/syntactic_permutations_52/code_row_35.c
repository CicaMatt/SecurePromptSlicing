#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100

// Simulating a session storage
typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

Session current_session = {""};

void set_session_username(const char *username) {
    strncpy(current_session.username, username, MAX_USERNAME_LEN);
}

int is_logged_in() {
    return strlen(current_session.username) > 0;
}

void do_login(const char *input_username, const char *input_password) {
    // Simulating correct credentials
    if (strcmp(input_username, "admin") == 0 && strcmp(input_password, "password123") == 0) {
        set_session_username(input_username);
        printf("Redirecting to the secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void index_page() {
    printf("Welcome!\n");
    printf("Click here to login: [Login Page](#login)\n");
}

void login_page() {
    char username[MAX_USERNAME_LEN];
    char password[100];

    printf("Username: ");
    scanf("%99s", username);
    printf("Password: ");
    scanf("%99s", password);

    do_login(username, password);
}

void show_secret_page() {
    if (is_logged_in()) {
        printf("Secret settings\n");
    } else {
        printf("Access denied. Please login first.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nMenu:\n1. Index Page\n2. Login Page\n3. Secret Page\n4. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                index_page();
                break;
            case 2:
                login_page();
                break;
            case 3:
                show_secret_page();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}