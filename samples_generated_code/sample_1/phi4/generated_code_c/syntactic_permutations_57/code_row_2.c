#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser;
int loggedIn = 0;

void displayLoginPage() {
    printf("Login Page\n");
    printf("Username: ");
    scanf("%s", currentUser.username);
    printf("Password: ");
    scanf("%s", currentUser.password);

    // Simulate login check
    if (strcmp(currentUser.username, "testuser") == 0 && 
        strcmp(currentUser.password, "password123") == 0) {
        loggedIn = 1;
    } else {
        loggedIn = 0;
    }
}

void displayChangeEmailPage() {
    char oldEmail[100];
    char newEmail[100];
    char confirmPassword[50];

    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Old Email: ");
    scanf("%s", oldEmail);
    printf("Confirm Password: ");
    scanf("%s", confirmPassword);

    // Verify user
    if (strcmp(oldEmail, currentUser.email) == 0 && 
        strcmp(confirmPassword, currentUser.password) == 0) {
        
        printf("New Email: ");
        scanf("%s", newEmail);

        // Simulate email existence check
        if (strlen(newEmail) > 0) { // Assume any non-empty string is a valid existing email
            strcpy(currentUser.email, newEmail);
            printf("Email changed successfully to %s\n", currentUser.email);
        } else {
            printf("Invalid new email.\n");
        }
    } else {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    // Initialize a user for demonstration
    strcpy(currentUser.username, "testuser");
    strcpy(currentUser.email, "oldemail@example.com");
    strcpy(currentUser.password, "password123");

    displayLoginPage();
    
    if (loggedIn) {
        displayChangeEmailPage();
    }

    return 0;
}