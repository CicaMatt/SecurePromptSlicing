#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD "password123"

typedef struct {
    char username[MAX_EMAIL_LEN];
    char email[MAX_EMAIL_LEN];
    int isLoggedIn;
} User;

void login(User *user) {
    printf("Enter your username: ");
    scanf("%s", user->username);
    printf("Enter your password: ");
    char inputPassword[MAX_EMAIL_LEN];
    scanf("%s", inputPassword);
    if (strcmp(inputPassword, PASSWORD) == 0) {
        strcpy(user->email, "user@example.com");
        user->isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        user->isLoggedIn = 0;
        printf("Login failed. Incorrect password.\n");
    }
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_EMAIL_LEN];
    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(oldEmail, user->email) == 0 && strcmp(confirmPassword, PASSWORD) == 0) {
        char newEmail[MAX_EMAIL_LEN];
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"", "", 0};

    int choice;
    do {
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
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}