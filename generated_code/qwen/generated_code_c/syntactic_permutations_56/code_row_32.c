#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int checkPassword(const char* enteredPassword, const char* storedPassword) {
    return strcmp(enteredPassword, storedPassword) == 0;
}

void changeEmail(char* currentEmail) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char storedPassword[] = "password123"; // This should be securely stored and retrieved

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (!checkPassword(confirmPassword, storedPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully to %s\n", currentEmail);
}

int main() {
    char userEmail[MAX_EMAIL_LENGTH] = "user@example.com"; // This should be securely stored and retrieved
    char loginPassword[MAX_PASSWORD_LENGTH];
    char storedPassword[] = "password123"; // This should be securely stored and retrieved

    printf("Enter your password to log in: ");
    scanf("%s", loginPassword);

    if (!checkPassword(loginPassword, storedPassword)) {
        printf("Login failed. Incorrect password.\n");
        return 1;
    }

    printf("Logged in successfully.\n");
    changeEmail(userEmail);

    return 0;
}