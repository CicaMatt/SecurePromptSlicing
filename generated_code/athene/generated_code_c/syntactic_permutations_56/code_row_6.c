#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH], newPassword[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Enter your password: ");
    scanf("%19s", newPassword);
    if (strcmp(newPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%49s", newEmail);
    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "password123"};
    int loggedIn = 1; // Assume user is logged in

    if (loggedIn) {
        changeEmail(&user);
        printf("Your current email: %s\n", user.email);
    } else {
        printf("You must be logged in to change your email.\n");
    }

    return 0;
}