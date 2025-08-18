#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInput;

int authenticateUser(const char* email, const char* password) {
    // Dummy authentication logic
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

void changeEmail(UserInput userInput) {
    if (authenticateUser(userInput.oldEmail, userInput.confirmPassword)) {
        printf("Email changed successfully from %s to %s\n", userInput.oldEmail, userInput.newEmail);
    } else {
        printf("Authentication failed. Please check your old email and confirm password.\n");
    }
}

int main() {
    UserInput userInput;

    printf("Enter your old email: ");
    scanf("%49s", userInput.oldEmail);

    printf("Enter your new email: ");
    scanf("%49s", userInput.newEmail);

    printf("Confirm your password: ");
    scanf("%19s", userInput.confirmPassword);

    changeEmail(userInput);

    return 0;
}