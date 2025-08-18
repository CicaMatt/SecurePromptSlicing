#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

User user = {"JohnDoe", "john@example.com", "password123", 0};

void login() {
    printf("Enter your password: ");
    char enteredPassword[MAX_PASSWORD_LENGTH];
    scanf("%s", enteredPassword);
    
    if (strcmp(enteredPassword, user.password) == 0) {
        user.isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Incorrect password. Login failed.\n");
    }
}

void changeEmail() {
    if (!user.isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user.email) != 0) {
        printf("The email you entered does not match our records. Email change failed.\n");
        return;
    }
    
    char passwordConfirmation[MAX_PASSWORD_LENGTH];
    printf("Confirm your password: ");
    scanf("%s", passwordConfirmation);
    
    if (strcmp(passwordConfirmation, user.password) != 0) {
        printf("Password confirmation failed. Email change not processed.\n");
        return;
    }

    char newEmail[MAX_EMAIL_LENGTH];
    printf("Enter your new email: ");
    scanf("%s", newEmail);

    strcpy(user.email, newEmail);
    printf("Your email has been successfully changed to %s\n", user.email);
}

int main() {
    int choice;
    
    do {
        printf("\n1. Login\n2. Change Email\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                changeEmail();
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}