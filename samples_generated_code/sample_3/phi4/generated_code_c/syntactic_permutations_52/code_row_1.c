#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

Session session;

void do_login(const char *username, const char *password) {
    // Hardcoded credentials for simplicity
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        strcpy(session.username, username);
        printf("Login successful. Redirecting to secret page...\n");
        secret_page();
    } else {
        printf("Invalid credentials.\n");
        index_page();
    }
}

void index_page() {
    printf("Index Page\n");
    printf("<a href='/login'>Login</a>\n");
}

void login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_USERNAME_LENGTH];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    do_login(username, password);
}

void secret_page() {
    if (strcmp(session.username, "admin") == 0) {
        printf("Secret Settings\n");
    } else {
        printf("Access Denied. Redirecting to index page...\n");
        index_page();
    }
}

int main() {
    char input;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1: Index Page\n2: Login Page\n3: Secret Page\n0: Exit\n");
        scanf(" %c", &input);

        switch (input) {
            case '1':
                index_page();
                break;
            case '2':
                login_page();
                break;
            case '3':
                secret_page();
                break;
            case '0':
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}