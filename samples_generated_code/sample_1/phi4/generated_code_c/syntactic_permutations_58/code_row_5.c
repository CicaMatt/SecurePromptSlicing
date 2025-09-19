#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser;
int isLoggedIn = 0;

void login() {
    printf("Enter username: ");
    scanf("%49s", currentUser.username);
    printf("Enter email: ");
    scanf("%99s", currentUser.email);
    printf("Enter password: ");
    scanf("%49s", currentUser.password);
    isLoggedIn = 1;
    printf("Login successful!\n");
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[100], newEmail[100], password[50];
    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    printf("Confirm your password: ");
    scanf("%49s", password);

    if (strcmp(oldEmail, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0) {
        printf("Enter new email: ");
        scanf("%99s", newEmail);
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    printf("Welcome to the Login System\n");

    login();

    char choice;
    do {
        printf("\nDo you want to change your email? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y') {
            changeEmail();
        }
    } while (choice != 'n');

    return 0;
}