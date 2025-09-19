#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser;
int loggedIn = 0;

void loginUser() {
    printf("Enter your email: ");
    scanf("%s", currentUser.email);
    printf("Enter your password: ");
    scanf("%s", currentUser.password);

    // Simulating a successful login
    if (strcmp(currentUser.email, "user@example.com") == 0 && 
        strcmp(currentUser.password, "password123") == 0) {
        loggedIn = 1;
        printf("Login successful!\n");
    } else {
        loggedIn = 0;
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", newPassword);

    if (strcmp(oldEmail, currentUser.email) == 0 && 
        strcmp(newPassword, currentUser.password) == 0) {
        printf("Enter new email: ");
        scanf("%s", currentUser.email);
        printf("Email changed successfully to %s\n", currentUser.email);
    } else {
        printf("Old email or password is incorrect.\n");
    }
}

int main() {
    loginUser();

    if (loggedIn) {
        changeEmail();
    }

    return 0;
}