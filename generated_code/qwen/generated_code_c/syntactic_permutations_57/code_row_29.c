#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password"

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[20];

    printf("Please enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Please enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Please confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect password. Email not changed.\n");
        return 1;
    }

    if (strcmp(oldEmail, "existing@example.com") != 0) { // Replace with actual email check
        printf("Old email does not match our records. Email not changed.\n");
        return 1;
    }

    printf("Email successfully changed from %s to %s\n", oldEmail, newEmail);
    return 0;
}