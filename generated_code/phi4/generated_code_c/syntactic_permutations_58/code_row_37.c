#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser;
int loggedIn = 0;

void login() {
    printf("Enter username: ");
    scanf("%49s", currentUser.username);
    printf("Enter email: ");
    scanf("%99s", currentUser.email);
    printf("Enter password: ");
    scanf("%49s", currentUser.password);

    loggedIn = 1;
}

int authenticate(char *email, char *password) {
    return (loggedIn && strcmp(currentUser.email, email) == 0 && strcmp(currentUser.password, password) == 0);
}

void changeEmail() {
    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[100];
    char newPassword[50];
    char newEmail[100];

    printf("Enter old email: ");
    scanf("%99s", oldEmail);
    printf("Confirm password: ");
    scanf("%49s", newPassword);

    if (!authenticate(oldEmail, newPassword)) {
        printf("Authentication failed. Email not changed.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%99s", newEmail);

    strcpy(currentUser.email, newEmail);
    printf("Email successfully changed to %s\n", currentUser.email);
}

int main() {
    printf("Welcome to the Login System!\n");
    
    login();

    int choice;
    do {
        printf("\n1. Change Email\n2. Logout\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                changeEmail();
                break;
            case 2:
                loggedIn = 0;
                printf("Logged out successfully.\n");
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