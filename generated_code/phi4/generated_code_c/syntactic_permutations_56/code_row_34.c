#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASS_LEN 50

// Function prototypes
void login();
void changeEmail();

int main() {
    int loggedIn = 0;
    
    while (1) {
        if (!loggedIn) {
            login();
        } else {
            changeEmail();
        }
    }

    return 0; // This will never be reached due to the infinite loop
}

// Function to handle user login
void login() {
    char username[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];
    printf("Enter your email: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // Dummy check for login credentials
    if (strcmp(username, "user@example.com") == 0 && strcmp(password, "password123") == 0) {
        printf("Login successful!\n");
        changeEmail();
    } else {
        printf("Incorrect email or password. Try again.\n");
    }
}

// Function to handle email change
void changeEmail() {
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASS_LEN];

    printf("\nEnter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    // Dummy check for old email and password
    if (strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, "password123") == 0) {
        if (strcmp(newEmail, oldEmail) != 0) {
            printf("Email changed successfully to %s\n", newEmail);
            // Here you would update the stored email address
        } else {
            printf("New email must be different from the old one.\n");
        }
    } else {
        printf("Incorrect email or password. Try again.\n");
    }
}