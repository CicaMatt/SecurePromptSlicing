#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User currentUser;
int loggedIn = 0;

void login() {
    printf("Enter your email: ");
    scanf("%s", currentUser.email);
    printf("Enter your password: ");
    scanf("%s", currentUser.password);

    // Simulating a successful login
    if (strcmp(currentUser.email, "user@example.com") == 0 && 
        strcmp(currentUser.password, "password123") == 0) {
        loggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your current (old) email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("The provided email does not match the logged-in user's email.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect confirm password. Email change failed.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    // Simulating a database with a single user
    strcpy(currentUser.email, "user@example.com");
    strcpy(currentUser.password, "password123");

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
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}