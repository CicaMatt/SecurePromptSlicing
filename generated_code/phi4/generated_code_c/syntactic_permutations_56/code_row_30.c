#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH + 1]; // +1 for null terminator
} User;

int authenticate(User *user, const char *inputPassword) {
    return strcmp(user->password, inputPassword) == 0;
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Old email does not match.\n");
        return;
    }
    if (!authenticate(user, confirmPassword)) {
        printf("Incorrect password.\n");
        return;
    }
    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    strncpy(user->email, newEmail, MAX_EMAIL_LENGTH);
    user->email[MAX_EMAIL_LENGTH - 1] = '\0'; // Ensure null-termination
    printf("Email changed successfully!\n");
}

int main() {
    User currentUser = {"user@example.com", "password123"};

    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[PASSWORD_LENGTH + 1];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail); // Limit input to avoid buffer overflow

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%20s", confirmPassword); // Limit input to avoid buffer overflow

    changeEmail(&currentUser, oldEmail, newEmail, confirmPassword);

    return 0;
}