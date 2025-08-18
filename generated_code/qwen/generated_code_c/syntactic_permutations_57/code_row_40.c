#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int main() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
    char storedPassword[MAX_PASSWORD] = "securepassword"; // This should be hashed and salted in a real application
    char loggedInUserEmail[MAX_EMAIL] = "user@example.com"; // Simulated logged-in user

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, loggedInUserEmail) != 0) {
        printf("You are not logged in with this email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, storedPassword) != 0) {
        printf("Incorrect password. Cannot change email.\n");
        return 1;
    }

    // Simulate changing the email
    strcpy(loggedInUserEmail, newEmail);
    printf("Email changed successfully to %s\n", loggedInUserEmail);

    return 0;
}