#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user) {
    printf("Enter your old email: ");
    scanf("%s", user->email);
    printf("Enter your password: ");
    scanf("%s", user->password);

    // Simulate a check against stored credentials
    if (strcmp(user->email, "example@domain.com") == 0 && strcmp(user->password, "correctPassword") == 0) {
        user->isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", newPassword);

    if (strcmp(oldEmail, user->email) == 0 && strcmp(newPassword, user->password) == 0) {
        printf("Enter new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Invalid old email or password.\n");
    }
}

int main() {
    User user = {"john_doe", "example@domain.com", "correctPassword", 0};

    int choice;
    do {
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
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}