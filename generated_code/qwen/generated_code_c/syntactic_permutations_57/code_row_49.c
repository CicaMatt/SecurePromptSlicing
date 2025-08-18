#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int authenticateUser(const char* email, const char* password) {
    // Dummy authentication logic
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

void changeEmail(User* user) {
    if (authenticateUser(user->oldEmail, user->password)) {
        printf("Email changed successfully from %s to %s.\n", user->oldEmail, user->newEmail);
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    User user;

    printf("Enter your old email: ");
    fgets(user.oldEmail, MAX_EMAIL, stdin);
    user.oldEmail[strcspn(user.oldEmail, "\n")] = 0; // Remove newline character

    if (authenticateUser(user.oldEmail, "")) {
        printf("Enter new email: ");
        fgets(user.newEmail, MAX_EMAIL, stdin);
        user.newEmail[strcspn(user.newEmail, "\n")] = 0;

        printf("Confirm password: ");
        fgets(user.password, MAX_PASSWORD, stdin);
        user.password[strcspn(user.password, "\n")] = 0;

        changeEmail(&user);
    } else {
        printf("You must be logged in to change your email.\n");
    }

    return 0;
}