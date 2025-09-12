#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

int isLoggedIn = 1; // Simulated login status for demonstration purposes.
const char *currentEmail = "user@example.com";
const char *password = "securePassword";

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    if (strcmp(currentEmail, oldEmail) != 0) {
        printf("The provided email does not match the logged-in user's email.\n");
        return;
    }

    printf("Enter new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    if (strlen(newEmail) == 0 || strlen(newEmail) > 99) {
        printf("Invalid new email.\n");
        return;
    }

    printf("Enter confirm password: ");
    fgets(confirmPassword, MAX_EMAIL_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (strcmp(password, confirmPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email successfully changed to: %s\n", currentEmail);
}

int main() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return 1;
    }
    
    changeEmail();
    return 0;
}