#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* enteredPassword, const User* user) {
    return strcmp(enteredPassword, user->password) == 0;
}

void changeEmail(User* user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your password to confirm: ");
    scanf("%s", confirmPassword);
    if (!authenticateUser(confirmPassword, user)) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);
    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    User user = {"user@example.com", "password123"};
    char loginPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your password to log in: ");
    scanf("%s", loginPassword);

    if (authenticateUser(loginPassword, &user)) {
        printf("Logged in successfully.\n");
        changeEmail(&user);
    } else {
        printf("Login failed. Incorrect password.\n");
    }

    return 0;
}