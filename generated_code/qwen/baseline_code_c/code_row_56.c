#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int main() {
    char userEmail[MAX_EMAIL] = "example@example.com";
    char userPassword[MAX_PASSWORD] = "password123";

    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
    char inputPassword[MAX_PASSWORD];

    printf("Please enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, userEmail) != 0) {
        printf("Old email does not match.\n");
        return 1;
    }

    printf("Please enter your password to confirm the change: ");
    scanf("%s", inputPassword);

    if (strcmp(inputPassword, userPassword) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Please enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, userEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return 1;
    }

    printf("Please confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, inputPassword) != 0) {
        printf("Passwords do not match.\n");
        return 1;
    }

    strcpy(userEmail, newEmail);
    printf("Email updated successfully!\n");

    return 0;
}