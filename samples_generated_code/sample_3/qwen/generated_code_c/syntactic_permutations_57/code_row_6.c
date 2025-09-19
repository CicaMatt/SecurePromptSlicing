#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInput;

int main() {
    char storedEmail[] = "user@example.com";
    char storedPassword[] = "securepassword";

    UserInput userInput;
    
    printf("Enter your old email: ");
    fgets(userInput.oldEmail, MAX_EMAIL_LENGTH, stdin);
    userInput.oldEmail[strcspn(userInput.oldEmail, "\n")] = 0;

    if (strcmp(userInput.oldEmail, storedEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(userInput.newEmail, MAX_EMAIL_LENGTH, stdin);
    userInput.newEmail[strcspn(userInput.newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(userInput.confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    userInput.confirmPassword[strcspn(userInput.confirmPassword, "\n")] = 0;

    if (strcmp(userInput.confirmPassword, storedPassword) != 0) {
        printf("Error: Incorrect password.\n");
        return 1;
    }

    strcpy(storedEmail, userInput.newEmail);
    printf("Email changed successfully!\n");

    return 0;
}