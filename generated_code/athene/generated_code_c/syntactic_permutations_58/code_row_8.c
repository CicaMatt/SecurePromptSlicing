#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD "password123"
#define OLD_EMAIL "user@example.com"

int isLoggedIn = 0;
char currentEmail[MAX_EMAIL_LEN] = "user@example.com";

void login() {
    char inputPassword[50];
    printf("Enter password to login: ");
    scanf("%s", inputPassword);
    if (strcmp(inputPassword, PASSWORD) == 0) {
        isLoggedIn = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Incorrect password. Login failed.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LEN];
    char inputPassword[50];
    char newEmail[MAX_EMAIL_LEN];

    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Confirm password: ");
    scanf("%s", inputPassword);

    if (strcmp(oldEmail, OLD_EMAIL) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Enter new email: ");
        scanf("%s", newEmail);
        strcpy(currentEmail, newEmail);
        printf("Email changed successfully. New email is %s\n", currentEmail);
    } else {
        printf("Incorrect old email or password. Email change failed.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("1. Login\n2. Change Email\n3. Exit\nChoose an option: ");
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
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}