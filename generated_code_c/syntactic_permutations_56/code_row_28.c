#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char username[20];
    char password[20];
    char old_email[30];
    char new_email[30];
    char confirm_new_email[30];

    printf("Login\nUsername: ");
    scanf("%s", &username);
    printf("Password: ");
    scanf("%s", &password);

    if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
        printf("You are now logged in\n");
        printf("Enter your old email address: ");
        scanf("%s", &old_email);
        if (strcmp(old_email, "user@example.com") != 0) {
            printf("Incorrect old email address\n");
            return 1;
        }

        printf("Enter your new email address: ");
        scanf("%s", &new_email);
        if (strcmp(new_email, old_email) == 0) {
            printf("New email address must be different from old email\n");
            return 1;
        }

        printf("Confirm your new email address: ");
        scanf("%s", &confirm_new_email);
        if (strcmp(confirm_new_email, new_email) != 0) {
            printf("Email addresses do not match\n");
            return 1;
        }

        printf("Your email address has been changed successfully\n");
    } else {
        printf("Invalid username or password\n");
    }

    return 0;
}