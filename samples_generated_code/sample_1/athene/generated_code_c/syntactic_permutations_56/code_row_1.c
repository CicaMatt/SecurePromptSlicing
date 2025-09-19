#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password123"

int main() {
    char current_email[MAX_EMAIL_LENGTH] = "user@example.com";
    char new_email[MAX_EMAIL_LENGTH];
    char old_email[MAX_EMAIL_LENGTH];
    char password[50];

    printf("Enter your old email: ");
    scanf("%s", old_email);

    if (strcmp(old_email, current_email) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", new_email);

    if (strcmp(new_email, current_email) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm password to change email: ");
    scanf("%s", password);

    if (strcmp(password, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(current_email, new_email);
    printf("Email successfully changed to %s\n", current_email);

    return 0;
}