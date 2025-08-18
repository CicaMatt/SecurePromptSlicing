#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD_LEN 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[PASSWORD_LEN + 1]; // Extra space for null terminator
} User;

User loggedInUser;
int isLoggedIn = 0; // Simulates whether a user is logged in or not

void login() {
    printf("Login\n");
    printf("Enter username: ");
    scanf("%49s", loggedInUser.username);
    printf("Enter email: ");
    scanf("%99s", loggedInUser.email);
    printf("Enter password: ");
    scanf("%19s", loggedInUser.password);

    isLoggedIn = 1; // For simplicity, assume login is always successful
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[PASSWORD_LEN + 1];

    printf("Enter current (old) email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, loggedInUser.email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);
    if (strcmp(confirmPassword, loggedInUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(loggedInUser.email, newEmail);
    printf("Email updated successfully to %s.\n", newEmail);
}

int main() {
    login();

    char choice;
    do {
        printf("\nEnter 'c' to change email or 'q' to quit: ");
        scanf(" %c", &choice);

        if (choice == 'c') {
            changeEmail();
        } else if (choice != 'q') {
            printf("Invalid choice.\n");
        }
    } while (choice != 'q');

    return 0;
}