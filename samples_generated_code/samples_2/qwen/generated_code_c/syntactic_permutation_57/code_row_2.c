#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

char* existingEmail = "user@example.com";
char* existingPassword = "securepassword";

int changeEmail(char* oldEmail, char* newEmail, char* confirmPassword) {
    if (strcmp(oldEmail, existingEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return 1;
    }
    if (strcmp(confirmPassword, existingPassword) != 0) {
        printf("Error: Incorrect password.\n");
        return 1;
    }
    strcpy(existingEmail, newEmail);
    printf("Email changed successfully.\n");
    return 0;
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}