#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int isLoggedIn = 0;
char userEmail[MAX_EMAIL] = "user@example.com";
char userPassword[MAX_PASSWORD] = "password";

void login() {
    char email[MAX_EMAIL], password[MAX_PASSWORD];
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(email, userEmail) == 0 && strcmp(password, userPassword) == 0) {
        isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL], newEmail[MAX_EMAIL], confirmPassword[MAX_PASSWORD];

    if (!isLoggedIn) {
        printf("Please log in first.\n");
        return;
    }

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(oldEmail, userEmail) != 0) {
        printf("The entered old email does not match.\n");
        return;
    }

    if (strcmp(newEmail, userEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return;
    }

    if (strcmp(confirmPassword, userPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(userEmail, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch(choice) {
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