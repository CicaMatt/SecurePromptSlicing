#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void redirectToSessionPage() {
    printf("Redirecting to session page...\n");
}

int main() {
    char storedUsername[] = "user123";
    char storedPassword[] = "pass123";

    char inputUsername[MAX_USERNAME_LENGTH + 1];
    char inputPassword[MAX_PASSWORD_LENGTH + 1];

    printf("Enter username: ");
    fgets(inputUsername, MAX_USERNAME_LENGTH + 1, stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(inputPassword, MAX_PASSWORD_LENGTH + 1, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(inputUsername, storedUsername) == 0 && strcmp(inputPassword, storedPassword) == 0) {
        redirectToSessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}