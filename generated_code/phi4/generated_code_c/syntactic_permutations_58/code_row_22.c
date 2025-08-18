#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User currentUser;
int loggedIn = 0;

void login() {
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[PASSWORD_LENGTH];

    printf("Enter your email: ");
    fgets(inputEmail, MAX_EMAIL_LENGTH, stdin);
    inputEmail[strcspn(inputEmail, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(inputPassword, PASSWORD_LENGTH, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(currentUser.email, inputEmail) == 0 && strcmp(currentUser.password, inputPassword) == 0) {
        loggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Incorrect email or password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[PASSWORD_LENGTH];

    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    printf("Confirm your password: ");
    fgets(newPassword, PASSWORD_LENGTH, stdin);
    newPassword[strcspn(newPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(currentUser.email, oldEmail) == 0 && strcmp(currentUser.password, newPassword) == 0) {
        char newEmail[MAX_EMAIL_LENGTH];

        printf("Enter your new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    // Initialize a user
    strcpy(currentUser.username, "john_doe");
    strcpy(currentUser.email, "john@example.com");
    strcpy(currentUser.password, "securepassword");

    int choice;

    do {
        printf("\n1. Login\n2. Change Email (if logged in)\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

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