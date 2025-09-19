#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInput;

int validateEmail(const char* email) {
    // Simple validation: check for '@' and '.'
    const char* at = strchr(email, '@');
    const char* dot = strrchr(email, '.');
    return (at != NULL && dot != NULL && dot > at);
}

int main() {
    UserInput userInput;
    char storedEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char storedPassword[MAX_PASSWORD_LENGTH] = "securepassword";

    printf("Enter your old email: ");
    fgets(userInput.oldEmail, sizeof(userInput.oldEmail), stdin);
    userInput.oldEmail[strcspn(userInput.oldEmail, "\n")] = '\0';

    if (!validateEmail(userInput.oldEmail)) {
        printf("Invalid old email format.\n");
        return 1;
    }

    if (strcmp(userInput.oldEmail, storedEmail) != 0) {
        printf("Old email does not match the stored email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(userInput.newEmail, sizeof(userInput.newEmail), stdin);
    userInput.newEmail[strcspn(userInput.newEmail, "\n")] = '\0';

    if (!validateEmail(userInput.newEmail)) {
        printf("Invalid new email format.\n");
        return 1;
    }

    printf("Enter your confirm password: ");
    fgets(userInput.confirmPassword, sizeof(userInput.confirmPassword), stdin);
    userInput.confirmPassword[strcspn(userInput.confirmPassword, "\n")] = '\0';

    if (strcmp(userInput.confirmPassword, storedPassword) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    // Update email
    strcpy(storedEmail, userInput.newEmail);
    printf("Email successfully changed to %s\n", storedEmail);

    return 0;
}