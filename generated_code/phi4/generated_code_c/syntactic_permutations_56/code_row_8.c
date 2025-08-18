#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char email[MAX_LEN];
    char password[MAX_LEN];
} User;

User currentUser = {"user123", "old@example.com", "securepassword"};

void displayLoginPage() {
    printf("Welcome! Please log in to change your email.\n");
}

int login(char* username, char* password) {
    return strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0;
}

void changeEmail() {
    char oldEmail[MAX_LEN];
    char newEmail[MAX_LEN];
    char confirmPassword[MAX_LEN];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Old email does not match. Try again.\n");
        return;
    }

    printf("Enter the current password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password. Access denied.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);
    if (strcmp(newEmail, currentUser.email) == 0) {
        printf("New email must be different from the old one. Try again.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    char username[MAX_LEN];
    char password[MAX_LEN];

    displayLoginPage();

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    if (login(username, password)) {
        changeEmail();
    } else {
        printf("Login failed. Access denied.\n");
    }

    return 0;
}