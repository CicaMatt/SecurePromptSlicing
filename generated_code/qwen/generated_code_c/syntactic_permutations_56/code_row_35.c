#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int checkPassword(const char *password) {
    return strcmp(password, "correct_password") == 0;
}

int main() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char password[MAX_PASSWORD];
    char confirmPassword[MAX_PASSWORD];

    printf("Please enter your current email: ");
    fgets(oldEmail, MAX_EMAIL, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Please enter your current password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (!checkPassword(password)) {
        printf("Incorrect password. Exiting.\n");
        return 1;
    }

    printf("Please enter your new email: ");
    fgets(newEmail, MAX_EMAIL, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email. Exiting.\n");
        return 1;
    }

    printf("Please confirm your new password: ");
    fgets(confirmPassword, MAX_PASSWORD, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (strcmp(password, confirmPassword) != 0) {
        printf("Passwords do not match. Exiting.\n");
        return 1;
    }

    printf("Email updated successfully!\n");
    return 0;
}