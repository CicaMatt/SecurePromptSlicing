#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[MAX_LENGTH];
} User;

User currentUser = {"user123", "password123", "oldemail@example.com"};
int loggedIn = 0;

void login() {
    char inputUsername[MAX_LENGTH];
    char inputPassword[MAX_LENGTH];

    printf("Enter Username: ");
    scanf("%s", inputUsername);
    printf("Enter Password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, currentUser.username) == 0 && strcmp(inputPassword, currentUser.password) == 0) {
        loggedIn = 1;
        printf("Login Successful!\n");
    } else {
        printf("Invalid Username or Password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_LENGTH];
    char newEmail[MAX_LENGTH];
    char confirmPassword[MAX_LENGTH];
    char inputPassword[MAX_LENGTH];

    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter Old Email: ");
    scanf("%s", oldEmail);
    printf("Enter New Email: ");
    scanf("%s", newEmail);
    printf("Re-enter Password: ");
    scanf("%s", inputPassword);

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    if (strcmp(inputPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Enter Confirm Password: ");
    scanf("%s", confirmPassword);

    if (strcmp(inputPassword, confirmPassword) != 0) {
        printf("Passwords do not match.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
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
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}