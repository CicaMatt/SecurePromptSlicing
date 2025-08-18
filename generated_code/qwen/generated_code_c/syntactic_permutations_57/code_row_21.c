#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int checkPassword(const char *inputPassword, const char *storedPassword) {
    return strcmp(inputPassword, storedPassword) == 0;
}

void changeEmail(char *currentEmail, char *password) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("The entered email does not match the current one.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (!checkPassword(confirmPassword, password)) {
        printf("Incorrect password. Please try again.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully!\nYour new email is %s\n", currentEmail);
}

int main() {
    char userPassword[MAX_PASSWORD_LENGTH] = "securepassword123";
    char userEmail[MAX_EMAIL_LENGTH] = "user@example.com";

    char loginPassword[MAX_PASSWORD_LENGTH];
    printf("Enter your password to log in: ");
    scanf("%s", loginPassword);

    if (!checkPassword(loginPassword, userPassword)) {
        printf("Login failed. Incorrect password.\n");
        return 1;
    }

    printf("Logged in successfully!\n");
    changeEmail(userEmail, userPassword);

    return 0;
}