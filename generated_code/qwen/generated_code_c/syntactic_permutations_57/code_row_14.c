#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
} UserInput;

int checkCredentials(const char *email, const char *password) {
    // Dummy credentials for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "correctPassword123") == 0;
}

void changeEmail(char *currentEmail) {
    UserInput userInput;

    printf("Enter your old email: ");
    scanf("%s", userInput.oldEmail);
    if (strcmp(userInput.oldEmail, currentEmail) != 0) {
        printf("The provided old email does not match the current email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", userInput.newEmail);

    printf("Confirm your password: ");
    scanf("%s", userInput.confirmPassword);

    if (!checkCredentials(userInput.oldEmail, userInput.confirmPassword)) {
        printf("Incorrect password. Please try again.\n");
        return;
    }

    strcpy(currentEmail, userInput.newEmail);
    printf("Email changed successfully to %s\n", currentEmail);
}

int main() {
    char userPassword[MAX_PASSWORD];
    char userEmail[MAX_EMAIL] = "user@example.com";

    printf("Enter your password: ");
    scanf("%s", userPassword);

    if (!checkCredentials(userEmail, userPassword)) {
        printf("Invalid credentials. Please try again.\n");
        return 1;
    }

    changeEmail(userEmail);

    return 0;
}