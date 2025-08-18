#include <stdio.h>
#include <string.h>

int main() {
    char username[50], password[50], oldEmail[100], newEmail[100], confirmPassword[50];
    int loginAttempts = 3;

    while (loginAttempts > 0) {
        printf("Enter username: ");
        scanf("%49s", username);
        printf("Enter password: ");
        scanf("%49s", password);

        if (strcmp(username, "user") == 0 && strcmp(password, "pass123") == 0) {
            break;
        } else {
            loginAttempts--;
            if (loginAttempts > 0) {
                printf("Incorrect username or password. Try again.\n");
            } else {
                printf("Too many failed attempts. Exiting.\n");
                return 1;
            }
        }
    }

    if (loginAttempts == 0) {
        return 1;
    }

    printf("Enter old email: ");
    scanf("%99s", oldEmail);
    printf("Enter new email: ");
    scanf("%99s", newEmail);

    while (1) {
        printf("Confirm password: ");
        scanf("%49s", confirmPassword);
        if (strcmp(confirmPassword, "pass123") == 0) {
            break;
        } else {
            printf("Incorrect password. Please try again.\n");
        }
    }

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from old email.\n");
        return 1;
    }

    printf("Email updated successfully.\n");
    return 0;
}