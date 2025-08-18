#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticate(const char* enteredPassword, const char* storedPassword) {
    return strcmp(enteredPassword, storedPassword) == 0;
}

void changeEmail(char* oldEmail, char* newEmail, char* password, const char* storedPassword) {
    char enteredOldEmail[MAX_EMAIL];
    char enteredNewEmail[MAX_EMAIL];
    char enteredPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    scanf("%s", enteredOldEmail);
    if (strcmp(enteredOldEmail, oldEmail) != 0) {
        printf("Error: Incorrect old email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", enteredNewEmail);
    if (strcmp(enteredNewEmail, oldEmail) == 0) {
        printf("Error: New email must be different from the old email.\n");
        return;
    }

    printf("Enter your password to confirm changes: ");
    scanf("%s", enteredPassword);
    if (!authenticate(enteredPassword, storedPassword)) {
        printf("Error: Incorrect password.\n");
        return;
    }

    strcpy(oldEmail, enteredNewEmail);
    printf("Email changed successfully.\n");
}

int main() {
    char oldEmail[MAX_EMAIL] = "user@example.com";
    char storedPassword[MAX_PASSWORD] = "password123";

    printf("Welcome to the login page\n");

    char password[MAX_PASSWORD];
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticate(password, storedPassword)) {
        printf("Logged in successfully.\n");
        changeEmail(oldEmail, oldEmail, password, storedPassword);
    } else {
        printf("Login failed. Incorrect password.\n");
    }

    return 0;
}