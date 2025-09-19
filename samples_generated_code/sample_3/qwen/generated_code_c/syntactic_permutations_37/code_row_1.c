#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from fgets input
        username[strcspn(username, "\n")] = '\0';
    }

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from fgets input
        password[strcspn(password, "\n")] = '\0';
    }

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Redirecting to success...\n");
    } else {
        printf("Invalid username or password.\n");
        printf("Redirecting to cant_login...\n");
    }

    return 0;
}