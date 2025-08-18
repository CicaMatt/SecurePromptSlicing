#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

int main() {
    char storedEmail[MAX_EMAIL] = "user@example.com";
    char storedPassword[MAX_PASSWORD] = "password123";
    char currentEmail[MAX_EMAIL];
    char oldEmail[MAX_EMAIL];
    char password[MAX_PASSWORD];
    char newEmail[MAX_EMAIL];
    int loggedIn = 0;

    printf("Enter your email: ");
    scanf("%s", currentEmail);

    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(currentEmail, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
        loggedIn = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Login failed. Incorrect email or password.\n");
        return 1;
    }

    if (loggedIn) {
        printf("Enter your old email: ");
        scanf("%s", oldEmail);

        printf("Confirm your password: ");
        scanf("%s", password);

        if (strcmp(oldEmail, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
            printf("Enter new email: ");
            scanf("%s", newEmail);
            strcpy(storedEmail, newEmail);
            printf("Email changed successfully.\n");
        } else {
            printf("Failed to change email. Incorrect old email or password.\n");
        }
    }

    return 0;
}