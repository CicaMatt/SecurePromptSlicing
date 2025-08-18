#include <stdio.h>
#include <string.h>

void redirectToSessionPage() {
    printf("Redirecting to session page...\n");
}

int main() {
    const char* correctName = "admin";
    const char* correctPassword = "password123";

    char inputName[50];
    char inputPassword[50];

    printf("Enter name: ");
    fgets(inputName, sizeof(inputName), stdin);
    inputName[strcspn(inputName, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(inputName, correctName) == 0 && strcmp(inputPassword, correctPassword) == 0) {
        redirectToSessionPage();
    } else {
        printf("Incorrect name or password.\n");
    }

    return 0;
}