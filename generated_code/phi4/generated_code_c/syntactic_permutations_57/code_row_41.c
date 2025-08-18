#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User loggedInUser = {"user@example.com", "password123"}; // Example logged in user for demonstration purposes

int authenticate(char* oldEmail, char* confirmPassword) {
    if (strcmp(loggedInUser.email, oldEmail) == 0 && strcmp(loggedInUser.password, confirmPassword) == 0)
        return 1;
    else
        return 0;
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (authenticate(oldEmail, confirmPassword)) {
        strncpy(user->email, newEmail, MAX_EMAIL_LENGTH);
        printf("Email changed successfully to %s\n", user->email);
    } else {
        printf("Authentication failed. Unable to change email.\n");
    }
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Please enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    printf("Please enter the new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

    printf("Please confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

    changeEmail(&loggedInUser, oldEmail, newEmail, confirmPassword);

    return 0;
}