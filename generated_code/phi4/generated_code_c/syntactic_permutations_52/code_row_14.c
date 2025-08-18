#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
} Session;

Session session;
int isLoggedIn = 0;

void do_login(const char *username, const char *password) {
    if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
        strcpy(session.username, username);
        isLoggedIn = 1;
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
    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    do_login(username, password);
}

void show_secret_page() {
    if (isLoggedIn) {
        printf("Secret settings\n");
    } else {
        printf("Please login to access this page.\n");
        show_index_page();
    }
}

int main() {
    char choice;
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Index Page\n");
        printf("2. Login Page\n");
        printf("3. Secret Page\n");
        printf("4. Exit\n");
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
            case '4':
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}