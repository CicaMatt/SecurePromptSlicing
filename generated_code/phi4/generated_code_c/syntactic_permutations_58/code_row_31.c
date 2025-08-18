#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser;
int loggedIn = 0;

void login() {
    printf("Enter your email: ");
    scanf("%s", currentUser.email);
    printf("Enter your password: ");
    scanf("%s", currentUser.password);

    // Simulating a successful login
    if (strcmp(currentUser.email, "user@example.com") == 0 && strcmp(currentUser.password, "password123") == 0) {
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

    char oldEmail[100], newPassword[50];
    printf("Enter your current (old) email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", newPassword);

    if (strcmp(oldEmail, currentUser.email) == 0 && strcmp(newPassword, currentUser.password) == 0) {
        printf("Enter new email: ");
        scanf("%s", currentUser.email);
        printf("Email changed successfully!\n");
    } else {
        printf("Old email or password is incorrect. Email not changed.\n");
    }
}

int main() {
    strcpy(currentUser.username, "JohnDoe");
    strcpy(currentUser.email, "user@example.com");
    strcpy(currentUser.password, "password123");

    login();

    if (loggedIn) {
        changeEmail();
    }

    return 0;
}