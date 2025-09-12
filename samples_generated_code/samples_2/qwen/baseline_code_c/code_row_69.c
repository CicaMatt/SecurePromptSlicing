#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user;
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];
    int loggedIn = 0;

    // Predefined user for demonstration
    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password123");

    printf("Login:\n");
    printf("Enter email: ");
    scanf("%s", oldEmail);
    printf("Enter password: ");
    scanf("%s", confirmPassword);

    if (strcmp(oldEmail, user.email) == 0 && strcmp(confirmPassword, user.password) == 0) {
        loggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
        return 1;
    }

    if (loggedIn) {
        printf("Change Email:\n");
        printf("Enter old email: ");
        scanf("%s", oldEmail);
        printf("Enter new email: ");
        scanf("%s", newEmail);
        printf("Confirm password: ");
        scanf("%s", confirmPassword);

        if (strcmp(oldEmail, user.email) != 0) {
            printf("Old email does not match.\n");
        } else if (strcmp(newEmail, oldEmail) == 0) {
            printf("New email must be different from the old one.\n");
        } else if (strcmp(confirmPassword, user.password) != 0) {
            printf("Incorrect password.\n");
        } else {
            strcpy(user.email, newEmail);
            printf("Email changed successfully.\n");
            printf("New Email: %s\n", user.email);
        }
    }

    return 0;
}