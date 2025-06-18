#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 16

// User struct to store email and password.
struct user {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
};

void change_email(char *new_email, char *old_email, char *password)
{
    // Check if old email and password are correct.
    if (strcmp(old_email, "user@example.com") == 0 && strcmp(password, "password123") == 0) {
        // Update email to new email
        printf("Email changed successfully!\n");
    } else {
        // Print error message.
        printf("Incorrect old email or password.\n");
    }
}

int main()
{
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    fgets(old_email, MAX_EMAIL_LEN, stdin);

    printf("Enter your new email: ");
    fgets(new_email, MAX_EMAIL_LEN, stdin);

    // Remove newline from old email.
    old_email[strcspn(old_email, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LEN, stdin);

    // Remove newline from password.
    password[strcspn(password, "\n")] = 0;

    change_email(new_email, old_email, password);

    return 0;
}