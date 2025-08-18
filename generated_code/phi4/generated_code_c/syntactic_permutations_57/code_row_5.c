#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"user@example.com", "password123"}; // Example logged-in user

int isLoggedIn(User user) {
    return strcmp(user.email, currentUser.email) == 0 && 
           strcmp(user.password, currentUser.password) == 0;
}

int isExistingEmail(const char *email) {
    // Simulate checking if the email exists in a database
    return strcmp(email, "user@example.com") == 0; // Example existing email
}

void changeEmail(User user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    printf("Changing email from %s to %s...\n", oldEmail, newEmail);
    currentUser.email = strdup(newEmail); // Update the current user's email
    printf("Email changed successfully!\n");
}

int main() {
    User login;
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%49s", login.email);
    printf("Enter your password: ");
    scanf("%19s", login.password);

    if (!isLoggedIn(login)) {
        printf("Invalid credentials. Please log in again.\n");
        return 1;
    }

    printf("Enter old email: ");
    scanf("%49s", oldEmail);
    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Old email does not match the current logged-in email.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%49s", newEmail);
    if (!isExistingEmail(newEmail)) {
        printf("New email must be an existing email.\n");
        return 1;
    }

    printf("Confirm password: ");
    scanf("%19s", confirmPassword);
    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect confirm password.\n");
        return 1;
    }

    changeEmail(currentUser, oldEmail, newEmail, confirmPassword);

    return 0;
}