#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

int main() {
    char username[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];
    int loginAttempts = 3;

    printf("Login to proceed:\n");
    while (loginAttempts > 0) {
        printf("Username: ");
        scanf("%99s", username);
        printf("Password: ");
        scanf("%49s", password);

        if (strcmp(username, "user") == 0 && strcmp(password, "pass123") == 0) {
            break;
        } else {
            loginAttempts--;
            if (loginAttempts > 0) {
                printf("Invalid credentials. Try again. (%d attempts left)\n", loginAttempts);
            } else {
                printf("Too many failed attempts. Exiting.\n");
                return 1;
            }
        }
    }

    if (loginAttempts == 0) {
        return 1;
    }

    printf("\nEnter your old email: ");
    scanf("%99s", oldEmail);

    while (1) {
        printf("Enter new email: ");
        scanf("%99s", newEmail);
        if (strcmp(oldEmail, newEmail) == 0) {
            printf("New email must be different from the old email. Try again.\n");
        } else {
            break;
        }
    }

    while (1) {
        printf("Confirm password: ");
        scanf("%49s", confirmPassword);
        if (strcmp(password, confirmPassword) != 0) {
            printf("Incorrect password. Try again.\n");
        } else {
            break;
        }
    }

    printf("Email update successful!\n");

    return 0;
}