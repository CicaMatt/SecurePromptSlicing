#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

int isLoggedIn = 0;
char currentEmail[MAX_EMAIL_LEN] = "example@example.com";
char password[MAX_PASSWORD_LEN] = "123456";

void login() {
    char inputEmail[MAX_EMAIL_LEN];
    char inputPassword[MAX_PASSWORD_LEN];
    
    printf("Enter email: ");
    scanf("%s", inputEmail);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputEmail, currentEmail) == 0 && strcmp(inputPassword, password) == 0) {
        isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter current email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Current email does not match.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);
    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm password to change email: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
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
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}