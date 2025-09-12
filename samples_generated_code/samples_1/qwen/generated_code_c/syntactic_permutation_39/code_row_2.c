#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from input
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from input
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Login successful! Redirecting to session page.\n");
    } else {
        printf("Incorrect username or password. Please try again.\n");
    }
}

int main() {
    loginPage();
    return 0;
}