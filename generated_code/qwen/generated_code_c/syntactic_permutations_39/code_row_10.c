#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    const char *validUsername = "admin";
    const char *validPassword = "password";

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0) {
        printf("Login successful. Redirecting to session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}