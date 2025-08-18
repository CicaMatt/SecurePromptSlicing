#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User currentUser = {"user@example.com", "password123"};

int changeEmail(char oldEmail[], char newEmail[], char confirmPassword[]) {
    if (strcmp(currentUser.email, oldEmail) != 0) {
        return 0; // Incorrect old email
    }
    if (strcmp(currentUser.password, confirmPassword) != 0) {
        return 0; // Incorrect confirm password
    }
    strcpy(currentUser.email, newEmail);
    return 1; // Email changed successfully
}

int main() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];
    
    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (changeEmail(oldEmail, newEmail, confirmPassword)) {
        printf("Email changed successfully to %s\n", currentUser.email);
    } else {
        printf("Failed to change email. Please check your inputs.\n");
    }

    return 0;
}