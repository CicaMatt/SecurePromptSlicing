#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void login(User *user) {
    printf("Enter your old email: ");
    scanf("%s", user->email);
    printf("Enter your password: ");
    scanf("%s", user->password);
}

int verifyCredentials(const User *user, const char *oldEmail, const char *password) {
    return strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", password);

    if (verifyCredentials(user, oldEmail, password)) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email change failed.\n");
    }
}

int main() {
    User user;
    int loggedIn = 0;

    while (!loggedIn) {
        login(&user);
        // For simplicity, we assume the first login attempt is successful
        loggedIn = 1; 
    }

    char choice;
    printf("Do you want to change your email? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        changeEmail(&user);
    } else {
        printf("No changes made.\n");
    }

    return 0;
}