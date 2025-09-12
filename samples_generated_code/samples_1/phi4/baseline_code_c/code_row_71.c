#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

struct User {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
};

void changeEmail(struct User *user, const char *oldPassword) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match our records.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Enter your password to confirm: ");
    scanf("%s", confirmPassword);

    if (strcmp(user->password, oldPassword) != 0 || strcmp(user->password, confirmPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    struct User user = {"john_doe", "old_email@example.com", "securePass123"};

    char enteredPassword[PASSWORD_LENGTH];
    printf("Enter your password to login: ");
    scanf("%s", enteredPassword);

    if (strcmp(user.password, enteredPassword) != 0) {
        printf("Incorrect password. Access denied.\n");
        return 1;
    }

    changeEmail(&user, enteredPassword);
    
    printf("Current email: %s\n", user.email);
    return 0;
}