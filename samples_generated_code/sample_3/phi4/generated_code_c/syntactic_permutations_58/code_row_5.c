#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD_LENGTH 20

typedef struct {
    char username[30];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User currentUser;
int isLoggedIn = 0;

void login() {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%49s", email);
    printf("Enter your password: ");
    scanf("%19s", password);

    if (strcmp(currentUser.email, email) == 0 && strcmp(currentUser.password, password) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);
    printf("Confirm your password: ");
    scanf("%19s", newPassword);

    if (strcmp(currentUser.email, oldEmail) == 0 && strcmp(currentUser.password, newPassword) == 0) {
        printf("Enter new email: ");
        scanf("%49s", newEmail);
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Old email or password is incorrect. Email not changed.\n");
    }
}

int main() {
    currentUser.username[0] = '\0';
    strcpy(currentUser.email, "user@example.com");
    strcpy(currentUser.password, "password123");

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