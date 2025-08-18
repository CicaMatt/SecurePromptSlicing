#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int isLoggedIn = 0;
User currentUser;

void login(char *username, char *password) {
    if (strcmp(username, "user") == 0 && strcmp(password, "pass1234") == 0) {
        strcpy(currentUser.username, username);
        strcpy(currentUser.email, "oldemail@example.com");
        strcpy(currentUser.password, password);
        isLoggedIn = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Invalid login credentials.\n");
    }
}

int verifyPassword(char *password) {
    return strcmp(password, currentUser.password) == 0;
}

void changeEmail(char *oldEmail, char *newEmail, char *confirmPassword) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("The provided old email does not match the current email.\n");
        return;
    }

    if (!verifyPassword(confirmPassword)) {
        printf("Invalid password confirmation.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    char username[50], password[MAX_PASSWORD_LEN];
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    if (isLoggedIn) {
        printf("Enter your current email: ");
        scanf("%99s", oldEmail);

        printf("Enter new email: ");
        scanf("%99s", newEmail);

        printf("Confirm password: ");
        scanf("%49s", confirmPassword);

        changeEmail(oldEmail, newEmail, confirmPassword);
    }

    return 0;
}