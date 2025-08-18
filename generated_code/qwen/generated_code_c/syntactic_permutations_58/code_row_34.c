#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int main() {
    char storedEmail[MAX_EMAIL] = "user@example.com";
    char storedPassword[MAX_PASSWORD] = "password123";
    char currentEmail[MAX_EMAIL];
    char oldEmail[MAX_EMAIL];
    char password[MAX_PASSWORD];
    char newEmail[MAX_EMAIL];

    printf("Enter your current email: ");
    fgets(currentEmail, MAX_EMAIL, stdin);
    currentEmail[strcspn(currentEmail, "\n")] = 0;

    if (strcmp(currentEmail, storedEmail) != 0) {
        printf("You are not logged in with the provided email.\n");
        return 1;
    }

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(oldEmail, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
        printf("Enter your new email: ");
        fgets(newEmail, MAX_EMAIL, stdin);
        newEmail[strcspn(newEmail, "\n")] = 0;
        strcpy(storedEmail, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}