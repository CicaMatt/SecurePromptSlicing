#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInput;

int isPasswordCorrect(const char* provided, const char* actual) {
    return strcmp(provided, actual) == 0;
}

int isExistingUser(const char* email) {
    // This function should check if the email exists in the database
    // For simplicity, we assume all emails exist
    return 1; 
}

void changeEmail(char* currentEmail, const char* newEmail) {
    strcpy(currentEmail, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    UserInput input;
    char storedPassword[MAX_PASSWORD_LENGTH] = "securepassword123"; // This should be securely stored and retrieved
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com"; // Current user's email

    printf("Enter your old email: ");
    scanf("%s", input.oldEmail);

    if (!isExistingUser(input.oldEmail)) {
        printf("Error: Old email does not exist.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", input.newEmail);

    printf("Confirm your password: ");
    scanf("%s", input.confirmPassword);

    if (!isPasswordCorrect(input.confirmPassword, storedPassword)) {
        printf("Error: Incorrect password.\n");
        return 1;
    }

    changeEmail(currentEmail, input.newEmail);

    return 0;
}