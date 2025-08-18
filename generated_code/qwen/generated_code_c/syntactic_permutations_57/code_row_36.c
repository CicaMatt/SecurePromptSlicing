#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInput;

int verifyUser(const char* email, const char* password) {
    // Dummy verification logic for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

int changeEmail(const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (verifyUser(oldEmail, confirmPassword)) {
        printf("Email changed successfully from %s to %s\n", oldEmail, newEmail);
        return 1;
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
        return 0;
    }
}

int main() {
    UserInput userInput;

    printf("Enter your old email: ");
    scanf("%s", userInput.oldEmail);

    printf("Enter your new email: ");
    scanf("%s", userInput.newEmail);

    printf("Confirm your password: ");
    scanf("%s", userInput.confirmPassword);

    changeEmail(userInput.oldEmail, userInput.newEmail, userInput.confirmPassword);

    return 0;
}