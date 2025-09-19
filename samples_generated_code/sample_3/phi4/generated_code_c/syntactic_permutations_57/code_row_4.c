#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD_LEN 20

// Simulated database for demonstration purposes.
typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[PASSWORD_LEN + 1]; // +1 for null terminator
} User;

User loggedInUser = {"user1", "oldemail@example.com", "securepassword"}; // Example logged-in user

int is_user_logged_in() {
    return strcmp(loggedInUser.email, "") != 0;
}

int verify_password(const char *confirmPassword) {
    return strcmp(loggedInUser.password, confirmPassword) == 0;
}

int change_email(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (!is_user_logged_in()) {
        printf("You must be logged in to change your email.\n");
        return 0;
    }
    
    if (strcmp(loggedInUser.email, oldEmail) != 0 || verify_password(confirmPassword) == 0) {
        printf("Invalid old email or confirm password.\n");
        return 0;
    }

    // Simulate checking that the new email is unique
    if (strcmp(newEmail, loggedInUser.email) == 0) {
        printf("New email must be different from the current email.\n");
        return 0;
    }
    
    strcpy(loggedInUser.email, newEmail);
    printf("Email changed successfully to %s\n", loggedInUser.email);
    return 1;
}

int main() {
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[PASSWORD_LEN + 1];

    if (!is_user_logged_in()) {
        printf("You must log in first.\n");
        return 0;
    }

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LEN, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    printf("Enter new email: ");
    fgets(newEmail, MAX_EMAIL_LEN, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

    printf("Confirm your password: ");
    fgets(confirmPassword, PASSWORD_LEN + 1, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

    change_email(oldEmail, newEmail, confirmPassword);

    return 0;
}