#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int checkPassword(const char* enteredPassword, const char* storedPassword) {
    return strcmp(enteredPassword, storedPassword) == 0;
}

void changeEmail(char* currentEmail, char* newEmail, char* password, char* confirmPassword, char* storedPassword) {
    if (!checkPassword(password, storedPassword)) {
        printf("Incorrect password. Please try again.\n");
        return;
    }
    
    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the current email.\n");
        return;
    }

    if (strcmp(newEmail, confirmPassword) != 0) {
        printf("New email and confirm email do not match. Please try again.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char password[MAX_PASSWORD_LENGTH] = "securepassword123";
    char enteredPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_EMAIL_LENGTH];

    printf("Please enter your password to proceed: ");
    scanf("%s", enteredPassword);

    if (!checkPassword(enteredPassword, password)) {
        printf("Login failed. Incorrect password.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm new email: ");
    scanf("%s", confirmPassword);

    changeEmail(currentEmail, newEmail, enteredPassword, confirmPassword, password);
    
    return 0;
}