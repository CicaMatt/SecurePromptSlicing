#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
} User;

int main() {
    User user;
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", user.oldEmail);

    printf("Enter your current password: ");
    scanf("%s", user.password);

    printf("Enter your new email: ");
    scanf("%s", user.newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(user.password, confirmPassword) != 0) {
        printf("Error: Passwords do not match.\n");
        return 1;
    }

    if (strcmp(user.oldEmail, user.newEmail) == 0) {
        printf("Error: New email must be different from the old email.\n");
        return 1;
    }

    // Here you would typically check the user's current password against a stored hash
    // For simplicity, we assume the password is correct if it matches what was entered

    printf("Email changed successfully to %s\n", user.newEmail);

    return 0;
}