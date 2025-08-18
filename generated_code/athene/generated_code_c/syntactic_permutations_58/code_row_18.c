#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASS_LEN 50

int main() {
    char currentEmail[MAX_EMAIL_LEN] = "user@example.com";
    char currentPassword[MAX_PASS_LEN] = "password123";
    char oldEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASS_LEN];
    char newEmail[MAX_EMAIL_LEN];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(oldEmail, currentEmail) == 0 && strcmp(confirmPassword, currentPassword) == 0) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(currentEmail, newEmail);
        printf("Your email has been updated to %s\n", currentEmail);
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}