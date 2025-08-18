#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char storedEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char storedPassword[MAX_PASSWORD_LENGTH] = "password123";
    int isLoggedIn = 0;
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(email, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
        isLoggedIn = 1;
    }

    if (isLoggedIn) {
        printf("Logged in successfully.\n");

        printf("Enter your old email: ");
        scanf("%s", email);
        printf("Confirm your password: ");
        scanf("%s", password);

        if (strcmp(email, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
            printf("Enter new email: ");
            scanf("%s", newEmail);
            strcpy(storedEmail, newEmail);
            printf("Email changed successfully.\n");
        } else {
            printf("Incorrect old email or password. Email not changed.\n");
        }
    } else {
        printf("Login failed.\n");
    }

    return 0;
}