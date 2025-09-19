#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

bool authenticateUser(const User* user, const char* oldEmail, const char* confirmPassword) {
    return strcmp(user->email, oldEmail) == 0 && strcmp(user->password, confirmPassword) == 0;
}

void changeEmail(User* user, const char* newEmail) {
    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User loggedInUser = {"example@example.com", "securepassword"};
    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    printf("Enter your password to confirm: ");
    scanf("%s", confirmPassword);

    if (!authenticateUser(&loggedInUser, oldEmail, confirmPassword)) {
        printf("Authentication failed. Please check your email and password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    changeEmail(&loggedInUser, newEmail);

    return 0;
}