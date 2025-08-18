#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    int loggedIn;
} User;

void login(User *user) {
    char inputEmail[MAX_EMAIL_LEN];
    char inputPassword[MAX_PASSWORD_LEN];

    printf("Enter email: ");
    scanf("%s", inputEmail);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(user->email, inputEmail) == 0 && strcmp(user->password, inputPassword) == 0) {
        user->loggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail(User *user) {
    if (!user->loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LEN];
    char newPassword[MAX_PASSWORD_LEN];
    char newEmail[MAX_EMAIL_LEN];

    printf("Enter old email: ");
    scanf("%s", oldEmail);
    printf("Confirm password: ");
    scanf("%s", newPassword);

    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, newPassword) == 0) {
        printf("Enter new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Invalid old email or password.\n");
    }
}

int main() {
    User user = {"john_doe", "old_email@example.com", "password123", 0};

    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
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
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}