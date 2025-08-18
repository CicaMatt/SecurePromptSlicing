#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[50];
} User;

User loggedInUser;
int isLoggedIn = 0;

void login(char username[], char password[]) {
    // For simplicity, assume a single user
    strcpy(loggedInUser.username, "user1");
    strcpy(loggedInUser.email, "old_email@example.com");
    strcpy(loggedInUser.password, "password123");

    if (strcmp(username, loggedInUser.username) == 0 && strcmp(password, loggedInUser.password) == 0) {
        isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

void changeEmail(char oldEmail[], char newPassword[], char newEmail[]) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(oldEmail, loggedInUser.email) == 0 && strcmp(newPassword, loggedInUser.password) == 0) {
        strcpy(loggedInUser.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Invalid old email or password.\n");
    }
}

void logout() {
    isLoggedIn = 0;
    printf("Logged out successfully.\n");
}

int main() {
    char username[50], password[50];
    char oldEmail[MAX_EMAIL_LENGTH], newPassword[50], newEmail[MAX_EMAIL_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    if (isLoggedIn) {
        printf("Enter your old email: ");
        scanf("%99s", oldEmail);
        printf("Enter your current password: ");
        scanf("%49s", newPassword);
        printf("Enter new email: ");
        scanf("%99s", newEmail);

        changeEmail(oldEmail, newPassword, newEmail);
    }

    logout();

    return 0;
}