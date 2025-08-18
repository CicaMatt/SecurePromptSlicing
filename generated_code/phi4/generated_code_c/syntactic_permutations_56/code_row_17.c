#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(User *user, const char *inputPassword) {
    return strcmp(user->password, inputPassword) == 0;
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Old email does not match our records.\n");
        return;
    }

    if (!authenticate(user, confirmPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email updated successfully to %s\n", user->email);
}

int main() {
    User currentUser = {"john_doe", "john@example.com", "securepassword123"};

    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    changeEmail(&currentUser, oldEmail, newEmail, confirmPassword);

    return 0;
}