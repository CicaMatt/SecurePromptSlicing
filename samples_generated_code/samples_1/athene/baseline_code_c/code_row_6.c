#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "correct_password"
#define OLD_EMAIL "old@example.com"

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[50];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);

    if (strcmp(oldEmail, OLD_EMAIL) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm password: ");
    scanf("%49s", confirmPassword);

    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Email successfully changed from %s to %s.\n", OLD_EMAIL, newEmail);
    strcpy(OLD_EMAIL, newEmail); // Note: This is a simplification. In practice, you would update the user's email in a database.
    return 0;
}