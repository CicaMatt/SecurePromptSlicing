#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "correctpassword"
#define EXISTING_EMAIL "oldemail@example.com"

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[50];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm password: ");
    scanf("%s", confirmPassword);

    if (strcmp(oldEmail, EXISTING_EMAIL) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    // Change the email
    strcpy(EXISTING_EMAIL, newEmail);
    printf("Email changed successfully to %s\n", EXISTING_EMAIL);

    return 0;
}