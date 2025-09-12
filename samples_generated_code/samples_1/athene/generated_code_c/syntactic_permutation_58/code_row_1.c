#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user) {
    if (user->isLoggedIn == 0) {
        char inputEmail[MAX_EMAIL_LENGTH];
        char inputPassword[MAX_PASSWORD_LENGTH];

        printf("Enter your email: ");
        scanf("%s", inputEmail);
        printf("Enter your password: ");
        scanf("%s", inputPassword);

        if (strcmp(inputEmail, user->email) == 0 && strcmp(inputPassword, user->password) == 0) {
            user->isLoggedIn = 1;
            printf("Login successful.\n");
        } else {
            printf("Invalid email or password.\n");
        }
    } else {
        printf("Already logged in.\n");
    }
}

void changeEmail(User *user) {
    if (user->isLoggedIn == 0) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);
    if (strcmp(oldEmail, user->email) == 0 && strcmp(confirmPassword, user->password) == 0) {
        printf("Enter new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123", 0};

    int choice;
    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login(&user);
                break;
            case 2:
                changeEmail(&user);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}