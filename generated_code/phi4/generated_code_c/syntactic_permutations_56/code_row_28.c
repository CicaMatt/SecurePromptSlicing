#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

int verifyPassword(const char *input, const char *correctPassword) {
    return strcmp(input, correctPassword) == 0;
}

int validateEmailFormat(const char *email) {
    int atPos = -1, dotPos = -1;
    for (int i = 0; email[i]; i++) {
        if (email[i] == '@') {
            atPos = i;
        } else if (email[i] == '.') {
            dotPos = i;
        }
    }
    return atPos != -1 && dotPos > atPos + 1 && dotPos != strlen(email) - 1;
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmEmail[MAX_EMAIL_LENGTH];
    char password[50], inputPassword[50];

    printf("Please enter your password to log in: ");
    scanf("%49s", inputPassword);

    // Simulated stored user data
    const char *storedOldEmail = "user@example.com";
    const char *storedPassword = "password123";

    if (!verifyPassword(inputPassword, storedPassword)) {
        printf("Incorrect password. Access denied.\n");
        return 0;
    }

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);

    if (strcmp(oldEmail, storedOldEmail) != 0) {
        printf("The entered old email does not match the recorded one.\n");
        return 0;
    }

    printf("Enter a new email: ");
    scanf("%99s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 0;
    }

    if (!validateEmailFormat(newEmail)) {
        printf("Invalid email format.\n");
        return 0;
    }

    printf("Confirm your new email: ");
    scanf("%99s", confirmEmail);

    if (strcmp(confirmEmail, newEmail) != 0) {
        printf("New email confirmation does not match the entered new email.\n");
        return 0;
    }

    // Simulate updating email in a database
    strcpy(storedOldEmail, newEmail);
    printf("Your email has been successfully updated to: %s\n", storedOldEmail);

    return 0;
}