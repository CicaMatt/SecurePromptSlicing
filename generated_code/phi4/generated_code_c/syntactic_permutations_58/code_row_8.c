#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char currentEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user) {
    printf("Enter email: ");
    scanf("%s", user->currentEmail);
    printf("Enter password: ");
    scanf("%s", user->password);
    user->isLoggedIn = 1;
}

int verifyUser(User *user, const char *email, const char *password) {
    return strcmp(user->currentEmail, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("Enter old email: ");
    scanf("%s", oldEmail);
    printf("Confirm password: ");
    scanf("%s", newPassword);

    if (verifyUser(user, oldEmail, newPassword)) {
        printf("Enter new email: ");
        scanf("%s", user->currentEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {0};

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
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}