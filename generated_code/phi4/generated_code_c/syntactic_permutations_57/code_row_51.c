#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[20]; // Simple representation, not secure.
} User;

User currentUser = {"user@example.com", "password123"}; // Example logged-in user.

int isLoggedIn(User *user) {
    // Simulated check if the user is logged in
    return strcmp(user->email, currentUser.email) == 0;
}

int verifyPassword(const char* inputPassword, const char* storedPassword) {
    return strcmp(inputPassword, storedPassword) == 0;
}

void changeEmail(User *user, const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (!isLoggedIn(user)) {
        printf("Error: User not logged in.\n");
        return;
    }

    if (strcmp(oldEmail, user->email) != 0) {
        printf("Error: Old email does not match current email.\n");
        return;
    }

    if (verifyPassword(confirmPassword, user->password)) {
        strncpy(user->email, newEmail, MAX_EMAIL_LENGTH);
        printf("Email changed successfully to %s\n", newEmail);
    } else {
        printf("Error: Incorrect password.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"}; // Example logged-in user.
    
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[20];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm password: ");
    fgets(confirmPassword, 20, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    changeEmail(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}