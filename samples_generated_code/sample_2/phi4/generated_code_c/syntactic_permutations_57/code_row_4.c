#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[50];
} User;

User currentUser = {"JohnDoe", "john@example.com", "password123"};

int isUserLoggedIn(User user, const char *email) {
    return strcmp(user.email, email) == 0;
}

int verifyPassword(const char *inputPassword) {
    return strcmp(currentUser.password, inputPassword) == 0;
}

int validateEmailFormat(const char *email) {
    // Simple validation: check if '@' and '.' are present
    return (strchr(email, '@') != NULL && strchr(strchr(email, '@') + 1, '.') != NULL);
}

void changeUserEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (!isUserLoggedIn(*user, oldEmail)) {
        printf("Error: You must be logged in with the correct email to change it.\n");
        return;
    }

    if (strcmp(oldEmail, user->email) != 0) {
        printf("Error: Old email does not match our records.\n");
        return;
    }

    if (!verifyPassword(confirmPassword)) {
        printf("Error: Incorrect confirm password.\n");
        return;
    }

    if (!validateEmailFormat(newEmail)) {
        printf("Error: Invalid new email format.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[50];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(confirmPassword, 50, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    changeUserEmail(&currentUser, oldEmail, newEmail, confirmPassword);

    return 0;
}