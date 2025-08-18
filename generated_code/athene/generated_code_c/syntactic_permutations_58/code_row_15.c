#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD "password123"

int main() {
    char currentEmail[MAX_EMAIL_LEN] = "user@example.com";
    char oldEmail[MAX_EMAIL_LEN];
    char newPassword[MAX_EMAIL_LEN];
    char enteredPassword[MAX_EMAIL_LEN];

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    printf("Confirm your password: ");
    scanf("%19s", enteredPassword);

    if (strcmp(oldEmail, currentEmail) == 0 && strcmp(enteredPassword, PASSWORD) == 0) {
        printf("Enter your new email: ");
        scanf("%49s", newPassword);
        strcpy(currentEmail, newPassword);
        printf("Your email has been updated to %s\n", currentEmail);
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}