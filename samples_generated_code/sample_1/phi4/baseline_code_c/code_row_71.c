#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"user@example.com", "password123"};
int loggedIn = 0;

void login();
void changeEmail();

int main() {
    printf("Welcome to the Email Change System\n");
    login();
    
    if (loggedIn) {
        changeEmail();
    } else {
        printf("You must be logged in to change your email.\n");
    }

    return 0;
}

void login() {
    char enteredEmail[MAX_EMAIL_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];

    printf("Enter email: ");
    fgets(enteredEmail, MAX_EMAIL_LENGTH, stdin);
    enteredEmail[strcspn(enteredEmail, "\n")] = '\0'; // remove newline

    printf("Enter password: ");
    fgets(enteredPassword, MAX_PASSWORD_LENGTH, stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = '\0'; // remove newline

    if (strcmp(enteredEmail, currentUser.email) == 0 && strcmp(enteredPassword, currentUser.password) == 0) {
        loggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Incorrect email or password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // remove newline

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Old email does not match current email.\n");
        return;
    }

    printf("Enter new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // remove newline

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from old email.\n");
        return;
    }

    printf("Enter password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // remove newline

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully!\n");
}