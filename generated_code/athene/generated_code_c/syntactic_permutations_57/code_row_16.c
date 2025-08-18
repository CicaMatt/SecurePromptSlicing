#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 254
#define PASSWORD "correctpassword"

int main() {
    char oldEmail[MAX_EMAIL_LENGTH + 1];
    char newEmail[MAX_EMAIL_LENGTH + 1];
    char confirmPassword[20];

    printf("Enter your old email: ");
    scanf("%254s", oldEmail);

    printf("Enter your new email: ");
    scanf("%254s", newEmail);

    printf("Confirm password to verify ownership: ");
    scanf("%19s", confirmPassword);

    if (strcmp(oldEmail, "user@example.com") != 0) {
        printf("Old email does not match the existing account.\n");
        return 1;
    }

    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect password. Cannot change email.\n");
        return 1;
    }

    // Simulate changing the email
    printf("Email changed successfully from %s to %s.\n", oldEmail, newEmail);
    return 0;
}