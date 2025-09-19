#include <stdio.h>
#include <string.h>

typedef struct {
    char currentEmail[100];
    char password[50];
} User;

void login(User *user) {
    printf("Enter your email: ");
    scanf("%s", user->currentEmail);
    printf("Enter your password: ");
    scanf("%s", user->password);
}

int verifyPassword(const User *user, const char *inputPassword) {
    return strcmp(user->password, inputPassword) == 0;
}

void changeEmail(User *user) {
    char oldEmail[100], newEmail[100], confirmPassword[50];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    
    if (strcmp(oldEmail, user->currentEmail) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, user->currentEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (!verifyPassword(user, confirmPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->currentEmail, newEmail);
    printf("Email changed successfully to %s\n", user->currentEmail);
}

int main() {
    User user = {"user@example.com", "password123"};

    login(&user);

    changeEmail(&user);

    return 0;
}