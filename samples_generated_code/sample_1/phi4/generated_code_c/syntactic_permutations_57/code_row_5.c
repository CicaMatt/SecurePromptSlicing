#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[20];
    bool isLoggedIn;
} User;

bool verifyPassword(const char *password, const char *confirmPassword) {
    return strcmp(password, confirmPassword) == 0;
}

bool isUserLoggedIn(User *user) {
    return user->isLoggedIn;
}

bool isExistingEmail(const char *email) {
    // For demonstration purposes, assume "existing@example.com" is the existing email
    const char existingEmail[] = "existing@example.com";
    return strcmp(email, existingEmail) == 0;
}

void changeEmail(User *user) {
    if (!isUserLoggedIn(user)) {
        printf("Error: User must be logged in to change their email.\n");
        return;
    }

    if (strcmp(user->oldEmail, user->newEmail) == 0) {
        printf("Error: New email must be different from the old email.\n");
        return;
    }

    if (!isExistingEmail(user->newEmail)) {
        printf("Error: The new email provided does not exist.\n");
        return;
    }

    // Assuming we have a password to verify against, for demonstration purposes:
    const char correctPassword[] = "password123";

    if (!verifyPassword(correctPassword, user->confirmPassword)) {
        printf("Error: Incorrect confirm password.\n");
        return;
    }

    strcpy(user->oldEmail, user->newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    User user = {"existing@example.com", "", "password123", true};

    // Simulating user input
    printf("Enter old email: ");
    fgets(user.oldEmail, MAX_EMAIL_LENGTH, stdin);
    user.oldEmail[strcspn(user.oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter new email: ");
    fgets(user.newEmail, MAX_EMAIL_LENGTH, stdin);
    user.newEmail[strcspn(user.newEmail, "\n")] = 0; // Remove newline character

    printf("Confirm password: ");
    fgets(user.confirmPassword, 20, stdin);
    user.confirmPassword[strcspn(user.confirmPassword, "\n")] = 0; // Remove newline character

    changeEmail(&user);

    return 0;
}