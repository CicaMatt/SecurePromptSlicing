#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User loggedInUser = {"user@example.com", "securepassword"};

int validateEmail(const char *email) {
    return strcmp(email, loggedInUser.email) == 0;
}

int validatePassword(const char *password) {
    return strcmp(password, loggedInUser.password) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    if (!validateEmail(oldEmail)) {
        printf("Error: Incorrect email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);
    if (!validatePassword(confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return;
    }

    strcpy(loggedInUser.email, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    char choice;

    while (1) {
        printf("\nLogin Page\n");
        printf("1. Change Email\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                changeEmail();
                break;
            case '2':
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}