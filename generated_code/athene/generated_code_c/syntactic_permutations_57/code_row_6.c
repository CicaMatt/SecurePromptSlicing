#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User loggedInUser = {"example@example.com", "securepassword"};

int changeEmail(char oldEmail[], char newEmail[], char confirmPassword[]) {
    if (strcmp(loggedInUser.email, oldEmail) != 0) {
        return 0; // Incorrect old email
    }
    if (strcmp(loggedInUser.password, confirmPassword) != 0) {
        return 0; // Incorrect password
    }
    strncpy(loggedInUser.email, newEmail, MAX_EMAIL_LEN - 1);
    loggedInUser.email[MAX_EMAIL_LEN - 1] = '\0';
    return 1;
}

int main() {
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (changeEmail(oldEmail, newEmail, confirmPassword)) {
        printf("Email successfully changed to %s\n", loggedInUser.email);
    } else {
        printf("Failed to change email. Please check your details and try again.\n");
    }

    return 0;
}