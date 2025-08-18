#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser;
int loggedIn = 0; // Simulates login status

void loginUser() {
    printf("Enter username: ");
    scanf("%s", currentUser.username);
    printf("Enter email: ");
    scanf("%s", currentUser.email);
    printf("Enter password: ");
    scanf("%s", currentUser.password);
    loggedIn = 1;
}

int verifyPassword(const char* inputPassword) {
    return strcmp(currentUser.password, inputPassword) == 0;
}

void changeEmail() {
    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[100];
    char newEmail[100];
    char confirmPass[50];

    printf("Enter old email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("The provided old email does not match the current email.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm password: ");
    scanf("%s", confirmPass);
    if (!verifyPassword(confirmPass)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    char option;

    while (1) {
        printf("\nMenu:\n");
        printf("L - Login\n");
        printf("C - Change Email\n");
        printf("Q - Quit\n");
        printf("Choose an option: ");
        scanf(" %c", &option);

        switch (option) {
            case 'l':
                loginUser();
                break;
            case 'c':
                changeEmail();
                break;
            case 'q':
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}