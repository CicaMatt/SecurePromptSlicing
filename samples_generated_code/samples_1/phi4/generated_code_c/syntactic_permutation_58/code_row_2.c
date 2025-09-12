#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void login(User *user, char *email, char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        printf("Login successful.\n");
    } else {
        printf("Incorrect email or password. Please try again.\n");
    }
}

void changeEmail(User *user, char *old_email, char *password, char *new_email) {
    if (strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0) {
        strcpy(user->email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"JohnDoe", "john@example.com", "password123"};
    char loginEmail[MAX_EMAIL_LENGTH], loginPassword[MAX_PASSWORD_LENGTH];
    int loggedIn = 0;

    while (1) {
        printf("Enter email to log in: ");
        scanf("%s", loginEmail);
        printf("Enter password: ");
        scanf("%s", loginPassword);

        if (strcmp(loginEmail, user.email) == 0 && strcmp(loginPassword, user.password) == 0) {
            loggedIn = 1;
            break;
        } else {
            printf("Incorrect email or password. Please try again.\n");
        }
    }

    char oldEmail[MAX_EMAIL_LENGTH], newPassword[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    while (loggedIn) {
        printf("\nCurrent Email: %s\n", user.email);
        printf("Enter your current email to change it: ");
        scanf("%s", oldEmail);
        printf("Enter your password to confirm: ");
        scanf("%s", newPassword);
        printf("Enter new email: ");
        scanf("%s", newEmail);

        changeEmail(&user, oldEmail, newPassword, newEmail);

        char choice;
        printf("Do you want to log out? (y/n): ");
        scanf(" %c", &choice); // Notice the space before %c to consume any newline character

        if (choice == 'y' || choice == 'Y') {
            loggedIn = 0;
            printf("Logged out successfully.\n");
        }
    }

    return 0;
}