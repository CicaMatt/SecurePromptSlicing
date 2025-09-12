#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[100];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};
int loggedIn = 0;

void login() {
    char inputEmail[100], inputPassword[100];

    printf("Enter email: ");
    scanf("%99s", inputEmail);
    printf("Enter password: ");
    scanf("%99s", inputPassword);

    if (strcmp(inputEmail, currentUser.email) == 0 && strcmp(inputPassword, currentUser.password) == 0) {
        loggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    char oldEmail[100], newEmail[100], confirmPassword[100];

    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    printf("Confirm your password: ");
    scanf("%99s", confirmPassword);

    if (strcmp(oldEmail, currentUser.email) == 0 && strcmp(confirmPassword, currentUser.password) == 0) {
        printf("Enter new email: ");
        scanf("%99s", newEmail);
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Invalid current email or password.\n");
    }
}

int main() {
    int choice;

    do {
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
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}