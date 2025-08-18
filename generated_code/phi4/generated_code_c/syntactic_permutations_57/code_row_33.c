#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[MAX_LENGTH];
} User;

User currentUser = {"user123", "password", "old_email@example.com"}; // Example logged-in user

int isUserLoggedIn(const User *user) {
    return strcmp(user->username, "") != 0;
}

int verifyPassword(const User *user, const char *inputPassword) {
    return strcmp(user->password, inputPassword) == 0;
}

int emailExists(const char *email) {
    // For simplicity in this example, assume all emails exist.
    // In a real application, you would check against a database.
    return strlen(email) > 5; // Dummy condition to simulate existing email
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(user->email, oldEmail) == 0 && verifyPassword(user, confirmPassword)) {
        strncpy(user->email, newEmail, MAX_LENGTH);
        printf("Email successfully changed to: %s\n", user->email);
    } else {
        printf("Failed to change email. Incorrect details provided.\n");
    }
}

int main() {
    if (!isUserLoggedIn(&currentUser)) {
        printf("You must be logged in to change your email.\n");
        return 1;
    }

    char oldEmail[MAX_LENGTH];
    char newEmail[MAX_LENGTH];
    char confirmPassword[MAX_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove trailing newline

    if (strcmp(currentUser.email, oldEmail) != 0) {
        printf("The provided current email does not match our records.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove trailing newline

    if (!emailExists(newEmail)) {
        printf("The provided new email does not exist.\n");
        return 1;
    }

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove trailing newline

    changeEmail(&currentUser, oldEmail, newEmail, confirmPassword);

    return 0;
}