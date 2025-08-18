#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

void redirectToSessionPage() {
    printf("Redirecting to Session Page...\n");
}

void displayIncorrectCredentialsMessage() {
    printf("Name or Password is incorrect.\n");
}

int main() {
    char correctName[MAX_NAME_LENGTH] = "user";
    char correctPassword[MAX_PASSWORD_LENGTH] = "password123";

    char inputName[MAX_NAME_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter name: ");
    fgets(inputName, MAX_NAME_LENGTH, stdin);
    inputName[strcspn(inputName, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(inputName, correctName) == 0 && strcmp(inputPassword, correctPassword) == 0) {
        redirectToSessionPage();
    } else {
        displayIncorrectCredentialsMessage();
    }

    return 0;
}