#include <stdio.h>
#include <string.h>

typedef struct {
    char email[100];
    char password[50];
} User;

User currentUser = {"user@example.com", "securepassword123"}; // Example logged-in user

int authenticate(char *oldEmail, char *confirmPassword) {
    if (strcmp(oldEmail, currentUser.email) == 0 && strcmp(confirmPassword, currentUser.password) == 0) {
        return 1;
    }
    return 0;
}

int isValidEmail(const char *email) {
    // Simple email validation: check for presence of '@' and '.'
    if (strchr(email, '@') != NULL && strchr(email + 1, '.') != NULL) {
        return 1;
    }
    return 0;
}

void changeEmail(char *oldEmail, char *newEmail, char *confirmPassword) {
    if (!authenticate(oldEmail, confirmPassword)) {
        printf("Authentication failed. Check your email or password.\n");
        return;
    }

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("The old email does not match the current account's email.\n");
        return;
    }

    if (!isValidEmail(newEmail)) {
        printf("Invalid new email format. Please provide a valid email address.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email updated successfully to %s\n", currentUser.email);
}

int main() {
    char oldEmail[100];
    char newEmail[100];
    char confirmPassword[50];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm password: ");
    scanf("%49s", confirmPassword);

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}