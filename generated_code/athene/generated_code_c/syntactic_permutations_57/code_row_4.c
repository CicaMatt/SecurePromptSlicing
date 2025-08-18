#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password123"
#define LOGGED_IN_USER "user@example.com"

int validate_email(const char *email) {
    // Simple validation: check for '@' and '.'
    if (strchr(email, '@') == NULL || strchr(email, '.') == NULL) {
        return 0;
    }
    return 1;
}

int change_email() {
    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], confirm_password[MAX_EMAIL_LENGTH];
    
    printf("Enter your old email: ");
    scanf("%99s", old_email);
    if (strcmp(old_email, LOGGED_IN_USER) != 0) {
        printf("Incorrect old email.\n");
        return -1;
    }

    printf("Enter your new email: ");
    scanf("%99s", new_email);
    if (!validate_email(new_email)) {
        printf("Invalid new email format.\n");
        return -1;
    }

    printf("Confirm password: ");
    scanf("%99s", confirm_password);
    if (strcmp(confirm_password, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return -1;
    }

    // If all checks pass, update the email
    strcpy(LOGGED_IN_USER, new_email);
    printf("Email changed successfully to: %s\n", LOGGED_IN_USER);
    return 0;
}

int main() {
    if (LOGGED_IN_USER[0] == '\0') {
        printf("You must be logged in to change your email.\n");
        return -1;
    }

    int result = change_email();
    if (result == 0) {
        printf("Operation completed successfully.\n");
    } else {
        printf("Failed to change email.\n");
    }

    return 0;
}