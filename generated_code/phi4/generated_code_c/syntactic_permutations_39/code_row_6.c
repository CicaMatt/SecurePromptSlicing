#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void redirectToSessionPage() {
    printf("Redirecting to session page...\n");
}

int main() {
    char correctUsername[MAX_USERNAME_LEN] = "admin";
    char correctPassword[MAX_PASSWORD_LEN] = "password123";

    char inputUsername[MAX_USERNAME_LEN];
    char inputPassword[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    fgets(inputUsername, MAX_USERNAME_LEN, stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(inputPassword, MAX_PASSWORD_LEN, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(inputUsername, correctUsername) == 0 && strcmp(inputPassword, correctPassword) == 0) {
        redirectToSessionPage();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}