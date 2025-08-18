#include <stdio.h>
#include <string.h>

void showLoginPage() {
    printf("Login Page\n");
    printf("Username: ");
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret123") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void showSecretPage() {
    printf("Secret settings\n");
}

int main() {
    char username[50];
    char password[50];

    showLoginPage();
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (do_login(username, password)) {
        showSecretPage();
    } else {
        printf("Login Failed!\n");
        printf("Try again or visit the login page.\n");
    }

    return 0;
}