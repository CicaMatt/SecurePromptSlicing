#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

typedef struct {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
} UserInput;

int authenticateUser(const char* email, const char* password) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

int isEmailValid(const char* email) {
    // Simple email validation (presence of '@' and '.')
    return strchr(email, '@') != NULL && strchr(email, '.') != NULL;
}

void changeEmail(char* oldEmail, const char* newEmail) {
    // Simulate changing the email
    strcpy(oldEmail, newEmail);
    printf("Email changed successfully to %s\n", newEmail);
}

int main() {
    UserInput userInput;
    char currentEmail[MAX_EMAIL] = "user@example.com";
    char password[MAX_PASSWORD];

    printf("Enter your old email: ");
    scanf("%49s", userInput.oldEmail);

    if (!isEmailValid(userInput.oldEmail)) {
        printf("Invalid old email format.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%49s", userInput.newEmail);

    if (!isEmailValid(userInput.newEmail)) {
        printf("Invalid new email format.\n");
        return 1;
    }

    printf("Confirm your password: ");
    scanf("%19s", userInput.confirmPassword);

    if (authenticateUser(currentEmail, userInput.confirmPassword)) {
        if (strcmp(userInput.oldEmail, currentEmail) == 0) {
            changeEmail(currentEmail, userInput.newEmail);
        } else {
            printf("Old email does not match the current email.\n");
        }
    } else {
        printf("Authentication failed. Incorrect password or old email.\n");
    }

    return 0;
}