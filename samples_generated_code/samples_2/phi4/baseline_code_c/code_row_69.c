#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser;
int isLoggedIn = 0;

void displayLoginPage() {
    printf("Login\n");
    printf("Username: ");
    scanf("%49s", currentUser.username);
    printf("Password: ");
    scanf("%49s", currentUser.password);

    if (strcmp(currentUser.username, "testuser") == 0 && strcmp(currentUser.password, "password123") == 0) {
        isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

void displayChangeEmailPage() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[100];
    char newEmail[100];
    char confirmPassword[50];

    printf("Old Email: ");
    scanf("%99s", oldEmail);
    
    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("The old email does not match the current email.\n");
        return;
    }

    printf("New Email: ");
    scanf("%99s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("The new email must be different from the old email.\n");
        return;
    }
    
    printf("Confirm Password: ");
    scanf("%49s", confirmPassword);

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email successfully changed to %s\n", currentUser.email);
}

int main() {
    displayLoginPage();
    
    if (isLoggedIn) {
        displayChangeEmailPage();
    }
    
    return 0;
}