#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD "securepassword"

int isLoggedIn = 0;
char currentEmail[MAX_EMAIL_LEN] = "user@example.com";

void login() {
    char password[100];
    printf("Enter password to log in: ");
    scanf("%s", password);
    if (strcmp(password, PASSWORD) == 0) {
        isLoggedIn = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Incorrect password. Login failed.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[100];
    
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Incorrect current email.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm password: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect confirm password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully to %s.\n", currentEmail);
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