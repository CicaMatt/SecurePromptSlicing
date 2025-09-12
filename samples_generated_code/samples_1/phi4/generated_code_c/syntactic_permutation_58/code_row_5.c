#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH + 1]; // Password string with a null terminator
} User;

User loggedInUser;
int isLoggedIn = 0;

void login() {
    User tempUser;
    printf("Enter username: ");
    scanf("%49s", tempUser.username);
    printf("Enter email: ");
    scanf("%99s", tempUser.email);
    printf("Enter password: ");
    scanf("%20s", tempUser.password);

    if (strcmp(tempUser.username, "user") == 0 && 
        strcmp(tempUser.email, "user@example.com") == 0 &&
        strcmp(tempUser.password, "password123") == 0) {
        loggedInUser = tempUser;
        isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials.\n");
    }
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[PASSWORD_LENGTH + 1];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, loggedInUser.email) != 0) {
        printf("Email does not match.\n");
        return;
    }

    printf("Confirm password: ");
    scanf("%20s", newPassword);
    if (strcmp(newPassword, loggedInUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%99s", newEmail);

    strcpy(loggedInUser.email, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                changeEmail();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}