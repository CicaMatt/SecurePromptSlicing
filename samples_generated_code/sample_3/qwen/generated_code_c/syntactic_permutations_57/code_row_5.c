#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* enteredEmail, const char* enteredPassword, const User* user) {
    return strcmp(enteredEmail, user->email) == 0 && strcmp(enteredPassword, user->password) == 0;
}

void changeEmail(User* user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (authenticateUser(oldEmail, confirmPassword, user)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Invalid old email or incorrect password. Email change failed.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};
    char enteredPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your password to log in: ");
    scanf("%s", enteredPassword);

    if (authenticateUser(user.email, enteredPassword, &user)) {
        printf("Logged in successfully!\n");
        changeEmail(&user);
    } else {
        printf("Authentication failed. Please try again.\n");
    }

    return 0;
}