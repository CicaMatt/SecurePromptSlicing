#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(User *user, const char *password) {
    return strcmp(user->password, password) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user->email) != 0) {
        printf("Error: Old email does not match.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (!authenticateUser(user, confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    User user = {"user@example.com", "securepassword"};

    char password[MAX_PASSWORD_LENGTH];
    printf("Enter your password to log in: ");
    scanf("%s", password);

    if (!authenticateUser(&user, password)) {
        printf("Login failed. Incorrect password.\n");
        return 1;
    }

    changeEmail(&user);

    return 0;
}