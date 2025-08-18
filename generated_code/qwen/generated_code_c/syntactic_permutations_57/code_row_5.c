#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInput;

int validateUser(const char* email, const char* password) {
    // Dummy validation logic for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

void changeEmail(UserInput userInput) {
    if (!validateUser(userInput.oldEmail, userInput.confirmPassword)) {
        printf("Invalid old email or password.\n");
        return;
    }
    // Dummy update logic for demonstration purposes
    printf("Email updated successfully from %s to %s\n", userInput.oldEmail, userInput.newEmail);
}

int main() {
    UserInput userInput;

    printf("Enter your current email: ");
    scanf("%99s", userInput.oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", userInput.newEmail);

    printf("Confirm your password: ");
    scanf("%49s", userInput.confirmPassword);

    changeEmail(userInput);

    return 0;
}