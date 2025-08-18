#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD "password123"

int main() {
    char username[MAX_EMAIL_LEN] = "user@example.com";
    char password[MAX_EMAIL_LEN];
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_EMAIL_LEN];

    printf("Enter your email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, username) != 0) {
        printf("Incorrect email.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(password, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email cannot be the same as the old email.\n");
        return 1;
    }

    printf("Confirm password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(username, newEmail);
    printf("Email changed successfully to %s\n", username);
    return 0;
}