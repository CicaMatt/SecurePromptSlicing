#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User loggedInUser = {"example_user", "old_email@example.com", "password123"};

int is_logged_in() {
    // In a real application, this would check session data or similar.
    return 1; // Assuming the user is logged in for simplicity
}

void change_email(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Old Email: ");
    scanf("%s", oldEmail);
    printf("New Email: ");
    scanf("%s", newEmail);
    printf("Confirm Password: ");
    scanf("%s", confirmPassword);

    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, confirmPassword) == 0) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully to %s\n", user->email);
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    if (is_logged_in()) {
        change_email(&loggedInUser);
    } else {
        printf("You must be logged in to change your email.\n");
    }

    return 0;
}