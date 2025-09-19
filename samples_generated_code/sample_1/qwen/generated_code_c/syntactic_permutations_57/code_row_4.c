#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"example@example.com", "password123"};

bool isEmailValid(const char* email) {
    return strcmp(email, currentUser.email) == 0;
}

bool isPasswordCorrect(const char* password) {
    return strcmp(password, currentUser.password) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    if (!isEmailValid(oldEmail)) {
        printf("Invalid email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (!isPasswordCorrect(confirmPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    char choice;

    printf("You are logged in as: %s\n", currentUser.email);
    printf("Do you want to change your email? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        changeEmail();
    } else {
        printf("No changes made.\n");
    }

    return 0;
}