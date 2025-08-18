#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"example@example.com", "password123"}; // Default user for demonstration purposes.

void displayLoginPage() {
    printf("Login Page\n");
    printf("Email: ");
}

int login(char *email, char *password) {
    if (strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0) {
        return 1;
    }
    return 0;
}

void displayChangeEmailPage() {
    printf("\nChange Email Page\n");
    printf("Old Email: ");
    char oldEmail[MAX_EMAIL_LENGTH];
    scanf("%s", oldEmail);
    
    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Incorrect old email. Try again.\n");
        return;
    }
    
    printf("New Email: ");
    char newEmail[MAX_EMAIL_LENGTH];
    scanf("%s", newEmail);
    
    if (strcmp(newEmail, currentUser.email) == 0) {
        printf("The new email must be different from the current email. Try again.\n");
        return;
    }

    printf("Confirm Password: ");
    char confirmPassword[MAX_PASSWORD_LENGTH];
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password. Try again.\n");
        return;
    }
    
    strcpy(currentUser.email, newEmail);
    printf("Email successfully changed to %s\n", newEmail);
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    displayLoginPage();
    scanf("%s", email);

    printf("Password: ");
    scanf("%s", password);

    if (!login(email, password)) {
        printf("Login failed. Please check your credentials and try again.\n");
        return 1;
    }

    displayChangeEmailPage();

    return 0;
}