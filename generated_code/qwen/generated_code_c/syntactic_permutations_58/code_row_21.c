#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char currentPassword[MAX_PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    int isLoggedIn = 0;

    printf("Enter your email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(oldEmail, currentEmail) == 0 && strcmp(password, currentPassword) == 0) {
        isLoggedIn = 1;
    }

    if (isLoggedIn) {
        printf("Logged in successfully.\n");
        printf("Enter new email: ");
        scanf("%s", newEmail);
        strcpy(currentEmail, newEmail);
        printf("Email changed successfully. New email is %s\n", currentEmail);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}