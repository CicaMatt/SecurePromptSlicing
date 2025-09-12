#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User loggedInUser = {"user1", "oldemail@example.com", "password123"};
int isLoggedIn = 0;
int maxLoginAttempts = 3;

void login() {
    int attempts = 0;
    while (attempts < maxLoginAttempts) {
        char inputEmail[MAX_EMAIL_LENGTH];
        char inputPassword[PASSWORD_LENGTH];

        printf("Enter email: ");
        scanf("%s", inputEmail);
        printf("Enter password: ");
        scanf("%s", inputPassword);

        if (strcmp(inputEmail, loggedInUser.email) == 0 && strcmp(inputPassword, loggedInUser.password) == 0) {
            isLoggedIn = 1;
            printf("Login successful!\n");
            return;
        } else {
            printf("Invalid email or password. Try again.\n");
            attempts++;
        }
    }

    printf("Too many failed login attempts.\n");
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char existingEmail[MAX_EMAIL_LENGTH];
    char newPassword[PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter current email: ");
    scanf("%s", existingEmail);
    if (strcmp(existingEmail, loggedInUser.email) != 0) {
        printf("The provided email does not match the logged-in user's email.\n");
        return;
    }

    printf("Enter confirm password: ");
    scanf("%s", newPassword);
    if (strcmp(newPassword, loggedInUser.password) != 0) {
        printf("Incorrect confirm password.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    strcpy(loggedInUser.email, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                changeEmail();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}