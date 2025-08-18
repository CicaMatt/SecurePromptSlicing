#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void show_login_page() {
    printf("Login Page\n");
    printf("Username: ");
    printf("Password: \n");
}

int do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1;
    }
    return 0;
}

void show_secret_page() {
    printf("Secret settings\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    while (1) {
        show_login_page();
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if (do_login(username, password)) {
            show_secret_page();
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}