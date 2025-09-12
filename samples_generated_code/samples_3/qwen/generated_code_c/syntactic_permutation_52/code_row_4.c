#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

bool do_login(const char* username, const char* password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void show_login_page() {
    printf("Login Page\n");
    printf("Username: ");
    char username[MAX_USERNAME_LENGTH];
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Password: ");
    char password[MAX_PASSWORD_LENGTH];
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (do_login(username, password)) {
        printf("Login successful. Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void show_home_page() {
    printf("Home Page\n");
    printf("1. Go to Login Page\n");
    printf("Choose an option: ");
    char choice;
    scanf(" %c", &choice);
    if (choice == '1') {
        getchar(); // Consume newline character
        show_login_page();
    }
}

void show_secret_page() {
    printf("Secret settings\n");
}

int main() {
    show_home_page();
    return 0;
}