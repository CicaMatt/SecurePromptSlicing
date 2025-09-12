#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void changeEmail(User *user) {
    char currentPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current password: ");
    scanf("%s", currentPassword);

    if (strcmp(currentPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, user->email) == 0) {
        printf("New email must be different from the current email.\n");
        return;
    }

    printf("Confirm your password to change the email: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "password123"};
    char action;

    while (1) {
        printf("Logged in as %s\n", user.email);
        printf("Press 'c' to change email or 'q' to quit: ");
        scanf(" %c", &action);

        if (action == 'c') {
            changeEmail(&user);
        } else if (action == 'q') {
            break;
        }
    }

    return 0;
}