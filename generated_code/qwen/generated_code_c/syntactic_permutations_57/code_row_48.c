#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInput;

int checkPassword(const char *storedPassword, const char *confirmPassword) {
    return strcmp(storedPassword, confirmPassword) == 0;
}

int updateEmail(char *currentEmail, const char *newEmail) {
    strcpy(currentEmail, newEmail);
    return 1; // Success
}

int main() {
    char storedEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char storedPassword[MAX_PASSWORD_LENGTH] = "password123";
    UserInput userInput;

    printf("Enter your old email: ");
    scanf("%s", userInput.oldEmail);

    if (strcmp(userInput.oldEmail, storedEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", userInput.newEmail);

    printf("Confirm your password: ");
    scanf("%s", userInput.confirmPassword);

    if (!checkPassword(storedPassword, userInput.confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return 1;
    }

    if (updateEmail(storedEmail, userInput.newEmail)) {
        printf("Email updated successfully!\n");
    } else {
        printf("Failed to update email.\n");
    }

    return 0;
}