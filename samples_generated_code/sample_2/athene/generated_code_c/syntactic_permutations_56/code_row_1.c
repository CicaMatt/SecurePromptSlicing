#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "securePassword123"

int main() {
    char username[MAX_EMAIL_LENGTH] = "user@example.com";
    char password[MAX_EMAIL_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Please enter your password to proceed: ");
    scanf("%s", password);

    if (strcmp(password, PASSWORD) != 0) {
        printf("Incorrect password. Access denied.\n");
        return 1;
    }

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, username) != 0) {
        printf("The entered email does not match the account email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the current email.\n");
        return 1;
    }

    strcpy(username, newEmail);
    printf("Your email has been successfully updated to %s\n", username);
    return 0;
}