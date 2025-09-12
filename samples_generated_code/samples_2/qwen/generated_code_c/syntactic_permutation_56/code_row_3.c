#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20
#define MAX_EMAIL_LENGTH 100

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmNewEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    // For simplicity, let's assume the correct password is "password123"
    if (strcmp(password, "password123") != 0) {
        printf("Incorrect password. Exiting.\n");
        return 1;
    }

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    while (1) {
        printf("Enter your new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = '\0';

        if (strcmp(newEmail, oldEmail) == 0) {
            printf("New email must be different from the old email. Please try again.\n");
        } else {
            break;
        }
    }

    while (1) {
        printf("Confirm your new email: ");
        fgets(confirmNewEmail, MAX_EMAIL_LENGTH, stdin);
        confirmNewEmail[strcspn(confirmNewEmail, "\n")] = '\0';

        if (strcmp(newEmail, confirmNewEmail) != 0) {
            printf("The emails do not match. Please try again.\n");
        } else {
            break;
        }
    }

    printf("Enter your password to confirm the changes: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (strcmp(password, confirmPassword) != 0) {
        printf("Incorrect password. Exiting.\n");
        return 1;
    }

    printf("Email updated successfully!\n");

    return 0;
}