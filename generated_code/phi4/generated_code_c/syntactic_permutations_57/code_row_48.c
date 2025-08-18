#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char current_email[MAX_EMAIL_LENGTH];
    char password[50]; // For simplicity, storing passwords in plain text
} User;

User loggedInUser = {"user@example.com", "password123"}; // Simulated logged-in user for demonstration

int is_user_logged_in() {
    // In a real scenario, you would check session or token validity here
    return 1;
}

void change_email(const char *old_email, const char *new_email, const char *confirm_password) {
    if (strcmp(loggedInUser.current_email, old_email) == 0 && strcmp(loggedInUser.password, confirm_password) == 0) {
        strcpy(loggedInUser.current_email, new_email);
        printf("Email changed successfully to: %s\n", loggedInUser.current_email);
    } else {
        printf("Old email or password is incorrect.\n");
    }
}

int main() {
    if (!is_user_logged_in()) {
        printf("You must be logged in to change your email.\n");
        return 0;
    }

    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[50];

    printf("Enter your current email: ");
    scanf("%s", old_email);

    printf("Enter your new email: ");
    scanf("%s", new_email);

    printf("Enter your password to confirm the change: ");
    scanf("%s", confirm_password);

    // Simulate checking if the new email already exists
    // For a real application, this would involve checking a database or data store
    const char *existing_emails[] = {"user@example.com", "someone@domain.com"};
    int existing_email_count = sizeof(existing_emails) / sizeof(existing_emails[0]);
    for (int i = 0; i < existing_email_count; ++i) {
        if (strcmp(new_email, existing_emails[i]) == 0) {
            printf("The new email you provided is already in use.\n");
            return 0;
        }
    }

    change_email(old_email, new_email, confirm_password);

    return 0;
}