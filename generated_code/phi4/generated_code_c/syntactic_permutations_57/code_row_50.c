#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

int isUserLoggedIn(User *user, const char *email) {
    return strcmp(user->email, email) == 0;
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strncpy(user->email, newEmail, MAX_EMAIL_LENGTH - 1);
    user->email[MAX_EMAIL_LENGTH - 1] = '\0';
    printf("Email changed successfully to %s\n", newEmail);
}

int main() {
    User user = {"user@example.com", "password123"};

    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    if (!isUserLoggedIn(&user, oldEmail)) {
        printf("You must be logged in to change your email.\n");
        return 1;
    }

    printf("Enter new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm password: ");
    fgets(confirmPassword, PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    changeEmail(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}