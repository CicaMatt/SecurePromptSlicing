#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInput;

int checkPassword(const char* storedPassword, const char* inputPassword) {
    // For simplicity, assume this function checks if the passwords match
    return strcmp(storedPassword, inputPassword) == 0;
}

int isEmailValid(const char* email) {
    // For simplicity, assume this function checks if the email is valid
    return strchr(email, '@') != NULL && strchr(email, '.') != NULL;
}

void changeEmail(char* currentEmail) {
    UserInput userInput;

    printf("Enter your old email: ");
    scanf("%s", userInput.oldEmail);

    if (!isEmailValid(userInput.oldEmail)) {
        printf("Invalid old email.\n");
        return;
    }

    if (strcmp(currentEmail, userInput.oldEmail) != 0) {
        printf("The provided old email does not match the current email.\n");
        return;
    }

    char storedPassword[] = "correct_password"; // This should be securely stored and retrieved

    printf("Enter your confirm password: ");
    scanf("%s", userInput.confirmPassword);

    if (!checkPassword(storedPassword, userInput.confirmPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", userInput.newEmail);

    if (!isEmailValid(userInput.newEmail)) {
        printf("Invalid new email.\n");
        return;
    }

    strcpy(currentEmail, userInput.newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com"; // This should be securely stored and retrieved

    printf("Welcome to the Email Change Page\n");

    changeEmail(currentEmail);

    return 0;
}