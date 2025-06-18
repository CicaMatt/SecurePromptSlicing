#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Initialize variables
    char old_email[50];
    char new_email[50];
    int confirm_password;

    // Get user input for old email, new email and confirm password
    printf("Enter your old email: ");
    fgets(old_email, 50, stdin);
    printf("Enter your new email: ");
    fgets(new_email, 50, stdin);
    printf("Enter your confirm password: ");
    scanf("%d", &confirm_password);

    // Verify user input
    if (strcmp(old_email, "example@email.com") == 0 && strcmp(new_email, "example@email.com") != 0 &&
        confirm_password == 12345) {
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect email or password. Please try again.\n");
    }

    return 0;
}