#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} UserCredentials;

int isUserLoggedIn = 0;
char currentUserEmail[MAX_EMAIL_LENGTH] = "user@example.com"; // Simulated logged-in user email

void changeEmail(UserCredentials credentials) {
    if (isUserLoggedIn && strcmp(credentials.oldEmail, currentUserEmail) == 0) {
        printf("Enter password: ");
        scanf("%s", credentials.password);

        if (strcmp(currentUserEmail, "user@example.com") == 0 && // Replace this check with actual hashed comparison in a real scenario
            strcmp(credentials.password, "correctPassword") == 0) { // Assume correct password is "correctPassword" for demo purposes

            strcpy(currentUserEmail, credentials.newEmail);
            printf("Email changed successfully to %s\n", currentUserEmail);
        } else {
            printf("Incorrect confirm password.\n");
        }
    } else {
        printf("Not logged in or incorrect old email.\n");
    }
}

int main() {
    UserCredentials credentials;

    // Simulating user login
    isUserLoggedIn = 1; // In a real scenario, handle authentication here

    printf("Enter your current (old) email: ");
    scanf("%s", credentials.oldEmail);

    printf("Enter new email: ");
    scanf("%s", credentials.newEmail);

    printf("Enter password to confirm change: ");
    scanf("%s", credentials.password);

    changeEmail(credentials);

    return 0;
}