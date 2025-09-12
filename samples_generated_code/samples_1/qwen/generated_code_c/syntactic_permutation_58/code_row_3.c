#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

bool isLoggedIn = false;
User user;

void login() {
    printf("Enter your email: ");
    scanf("%s", user.email);
    printf("Enter your password: ");
    scanf("%s", user.password);
    isLoggedIn = true;
}

bool changeEmail(const char* oldEmail, const char* password, const char* newEmail) {
    if (isLoggedIn) {
        if (strcmp(user.email, oldEmail) == 0 && strcmp(user.password, password) == 0) {
            strcpy(user.email, newEmail);
            return true;
        }
    }
    return false;
}

int main() {
    login();

    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("To change your email, please enter your current details:\n");
    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", password);
    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (changeEmail(oldEmail, password, newEmail)) {
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }

    return 0;
}