#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser;
int isLoggedIn = 0;

void login() {
    printf("Enter your email: ");
    fgets(currentUser.email, sizeof(currentUser.email), stdin);
    currentUser.email[strcspn(currentUser.email, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(currentUser.password, sizeof(currentUser.password), stdin);
    currentUser.password[strcspn(currentUser.password, "\n")] = '\0'; // Remove newline character

    if (strcmp(currentUser.email, "user@example.com") == 0 && strcmp(currentUser.password, "password123") == 0) {
        printf("Login successful!\n");
        isLoggedIn = 1;
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    printf("Confirm your password: ");
    fgets(newPassword, sizeof(newPassword), stdin);
    newPassword[strcspn(newPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(currentUser.email, oldEmail) == 0 && strcmp(currentUser.password, newPassword) == 0) {
        printf("Enter your new email: ");
        fgets(currentUser.email, sizeof(currentUser.email), stdin);
        currentUser.email[strcspn(currentUser.email, "\n")] = '\0'; // Remove newline character
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect current email or password. Email not changed.\n");
    }
}

int main() {
    login();
    changeEmail();

    return 0;
}