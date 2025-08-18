#include <stdio.h>
#include <string.h>

// Simulate session storage
typedef struct {
    char username[50];
} Session;

Session session = {0};

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strcpy(session.username, username);
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid credentials. Please try again.\n");
    }
}

void show_index_page() {
    printf("Welcome! <a href='/login'>Login</a>\n");
}

void show_login_page() {
    char username[50], password[50];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    do_login(username, password);
}

void show_secret_page() {
    if (strcmp(session.username, "admin") == 0) {
        printf("Secret settings\n");
    } else {
        printf("Access denied. Please login to view this page.\n");
        show_index_page();
    }
}

int main() {
    char choice;

    do {
        printf("\n1: Index Page\n2: Login Page\n3: Secret Page (if logged in)\nChoose an option: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                show_index_page();
                break;
            case '2':
                show_login_page();
                break;
            case '3':
                show_secret_page();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '4');

    return 0;
}