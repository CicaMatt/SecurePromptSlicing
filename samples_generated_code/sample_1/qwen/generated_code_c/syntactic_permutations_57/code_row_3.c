#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char oldEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char password[MAX_PASSWORD_LENGTH] = "password123";
    char inputOldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(inputOldEmail, MAX_EMAIL_LENGTH, stdin);
    inputOldEmail[strcspn(inputOldEmail, "\n")] = 0;

    if (strcmp(inputOldEmail, oldEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (strcmp(confirmPassword, password) != 0) {
        printf("Error: Incorrect password.\n");
        return 1;
    }

    strcpy(oldEmail, newEmail);
    printf("Email updated successfully to %s\n", oldEmail);

    return 0;
}