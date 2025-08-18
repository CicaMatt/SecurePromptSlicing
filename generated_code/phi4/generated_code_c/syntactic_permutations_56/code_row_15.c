#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char currentEmail[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    if (strcmp(user->currentEmail, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter your password: ");
    fgets(user->password, sizeof(user->password), stdin);
    user->password[strcspn(user->password, "\n")] = 0; // Remove newline character

    printf("Enter new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    if (strcmp(user->currentEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Passwords do not match.\n");
        return;
    }

    strcpy(user->currentEmail, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    User user = {"user@example.com", "password123"};

    changeEmail(&user);

    printf("Current email: %s\n", user.currentEmail);

    return 0;
}