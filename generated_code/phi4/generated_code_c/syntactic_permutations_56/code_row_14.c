#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100

typedef struct {
    char username[50];
    char password[50];
    char email[MAX_EMAIL_LEN];
} User;

User currentUser = {"user", "pass123", "user@example.com"};

int authenticate(const char *username, const char *password) {
    return strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[50];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);
    if (strcmp(newEmail, currentUser.email) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (authenticate(currentUser.username, confirmPassword)) {
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect password. Email change failed.\n");
    }
}

void login() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Login successful!\n");
        changeEmail();
    } else {
        printf("Incorrect username or password. Please try again.\n");
    }
}

int main() {
    login();
    return 0;
}