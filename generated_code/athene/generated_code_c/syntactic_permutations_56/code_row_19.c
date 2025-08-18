#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

int main() {
    char username[MAX_EMAIL] = "user";
    char password[MAX_PASSWORD] = "pass123";
    char currentEmail[MAX_EMAIL] = "user@example.com";
    char oldEmail[MAX_EMAIL], newEmail[MAX_EMAIL], confirmPassword[MAX_PASSWORD], inputPassword[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%49s", username);

    if (strcmp(username, "user") != 0) {
        printf("Invalid username.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%19s", inputPassword);

    if (strcmp(inputPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Old email does not match the registered email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%49s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm password: ");
    scanf("%19s", confirmPassword);

    if (strcmp(confirmPassword, password) != 0) {
        printf("Confirmation password does not match the original password.\n");
        return 1;
    }

    printf("Email updated successfully!\n");

    return 0;
}