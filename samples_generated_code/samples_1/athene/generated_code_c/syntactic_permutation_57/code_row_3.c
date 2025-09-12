#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD "correctpassword"

int main() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_EMAIL_LEN];
    const char *existingEmail = "user@example.com";

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm password: ");
    scanf("%s", confirmPassword);

    if (strcmp(oldEmail, existingEmail) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Email changed successfully from %s to %s.\n", existingEmail, newEmail);
    return 0;
}