#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 254
#define PASSWORD "securepassword"

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "";
    char enteredOldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[100];

    printf("Enter your old email: ");
    scanf("%s", enteredOldEmail);
    if (strcmp(enteredOldEmail, currentEmail) != 0 && strlen(currentEmail) == 0) {
        printf("You must be logged in to change your email.\n");
        return 1;
    } else if (strcmp(enteredOldEmail, currentEmail) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm password to change email: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(currentEmail, newEmail);
    printf("Email successfully changed to %s\n", currentEmail);

    return 0;
}