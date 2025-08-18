#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInput;

int verifyUser(const char* oldEmail, const char* confirmPassword) {
    // This is a placeholder function. In real applications, you would check the database.
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, "securepassword123") == 0;
}

void changeEmail(char* newEmail) {
    // This is a placeholder function. In real applications, you would update the user's email in the database.
    printf("Email changed successfully to: %s\n", newEmail);
}

int main() {
    UserInput userInput;

    printf("Enter your old email: ");
    fgets(userInput.oldEmail, MAX_EMAIL_LENGTH, stdin);
    userInput.oldEmail[strcspn(userInput.oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your new email: ");
    fgets(userInput.newEmail, MAX_EMAIL_LENGTH, stdin);
    userInput.newEmail[strcspn(userInput.newEmail, "\n")] = 0; // Remove newline character

    printf("Enter your confirm password: ");
    fgets(userInput.confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    userInput.confirmPassword[strcspn(userInput.confirmPassword, "\n")] = 0; // Remove newline character

    if (verifyUser(userInput.oldEmail, userInput.confirmPassword)) {
        changeEmail(userInput.newEmail);
    } else {
        printf("Failed to verify user. Please check your old email and confirm password.\n");
    }

    return 0;
}