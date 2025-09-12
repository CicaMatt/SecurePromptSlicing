#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password123"

int main() {
    char username[MAX_EMAIL_LENGTH] = "user@example.com";
    char password[MAX_EMAIL_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_EMAIL_LENGTH];

    printf("Enter your password to log in: ");
    scanf("%s", password);

    if (strcmp(password, PASSWORD) != 0) {
        printf("Incorrect password. Login failed.\n");
        return 1;
    }

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, username) != 0) {
        printf("Old email does not match the account email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email cannot be the same as the old email.\n");
        return 1;
    }

    printf("Confirm password to change email: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect password. Email change failed.\n");
        return 1;
    }

    strcpy(username, newEmail);
    printf("Email changed successfully. New email is %s\n", username);

    return 0;
}