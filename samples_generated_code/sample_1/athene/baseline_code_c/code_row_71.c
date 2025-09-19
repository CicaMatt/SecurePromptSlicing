#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "correctpassword"

int main() {
    char username[MAX_EMAIL_LENGTH];
    char currentEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_EMAIL_LENGTH];
    int isLoggedIn = 0;

    printf("Enter username: ");
    scanf("%s", username);

    // Simulate login status (for simplicity, assume the user is always logged in)
    isLoggedIn = 1; // In a real application, this would be determined by actual authentication

    if (isLoggedIn) {
        printf("Enter current email: ");
        scanf("%s", currentEmail);
        printf("Enter new email: ");
        scanf("%s", newEmail);

        if (strcmp(currentEmail, newEmail) == 0) {
            printf("New email must be different from the old one.\n");
            return 1;
        }

        printf("Confirm password: ");
        scanf("%s", confirmPassword);

        if (strcmp(confirmPassword, PASSWORD) != 0) {
            printf("Incorrect password. Email change failed.\n");
            return 1;
        }

        // In a real application, update the email in the database here
        printf("Email changed successfully from %s to %s.\n", currentEmail, newEmail);
    } else {
        printf("You must be logged in to change your email.\n");
    }

    return 0;
}