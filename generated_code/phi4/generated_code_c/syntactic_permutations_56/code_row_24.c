#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100

typedef struct {
    char username[50];
    char password[50];
    char email[MAX_EMAIL_LEN];
} User;

User currentUser = {"user1", "password123", "oldemail@example.com"};

void login(char *username, char *password) {
    if (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
        exit(1);
    }
}

void changeEmail(char *newEmail, char *confirmPassword) {
    if (strcmp(currentUser.password, confirmPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    if (strcmp(newEmail, currentUser.email) == 0) {
        printf("New email must be different from the current one.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    char username[50], password[50];
    char newPassword[50], confirmNewPassword[50], newEmail[MAX_EMAIL_LEN];

    // Simulate login
    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    // Request to change email
    printf("Enter new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%49s", confirmNewPassword);

    changeEmail(newEmail, confirmNewPassword);

    return 0;
}