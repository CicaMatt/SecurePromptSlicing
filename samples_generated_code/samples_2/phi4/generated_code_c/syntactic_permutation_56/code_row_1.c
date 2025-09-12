#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[50];
    char password[MAX_PASSWORD_LEN];
    char email[MAX_EMAIL_LEN];
} User;

User loggedInUser = {"user1", "password123", "oldemail@example.com"};

void login() {
    char inputUsername[50], inputPassword[MAX_PASSWORD_LEN];

    printf("Enter Username: ");
    scanf("%49s", inputUsername);
    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, loggedInUser.username) == 0 && strcmp(inputPassword, loggedInUser.password) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
        exit(1);
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);

    if (strcmp(oldEmail, loggedInUser.email) != 0) {
        printf("Old email does not match.\n");
        exit(1);
    }

    printf("Enter new email: ");
    scanf("%99s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        exit(1);
    }

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (strcmp(confirmPassword, loggedInUser.password) != 0) {
        printf("Incorrect password.\n");
        exit(1);
    }

    strcpy(loggedInUser.email, newEmail);
    printf("Email changed successfully to %s\n", loggedInUser.email);
}

int main() {
    login();
    changeEmail();

    return 0;
}