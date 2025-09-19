#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void login(User *user) {
    printf("Enter your current email: ");
    scanf("%s", user->email);
    printf("Enter your password: ");
    scanf("%s", user->password);
}

int verifyUser(const User *currentUser, const char *oldEmail, const char *password) {
    return strcmp(currentUser->email, oldEmail) == 0 && strcmp(currentUser->password, password) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your password to confirm: ");
    scanf("%s", password);

    if (verifyUser(user, oldEmail, password)) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email change failed.\n");
    }
}

int main() {
    User user;
    login(&user);

    printf("Do you want to change your email? (y/n): ");
    char choice;
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        changeEmail(&user);
    }

    return 0;
}