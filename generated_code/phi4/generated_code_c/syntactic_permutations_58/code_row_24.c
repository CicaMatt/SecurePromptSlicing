#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char currentEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int isLoggedIn = 0;
User currentUser = {"user@example.com", "password123"};

void login() {
    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (strcmp(currentUser.currentEmail, email) == 0 && strcmp(currentUser.password, password) == 0) {
        isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH], newPassword[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    printf("Confirm your password: ");
    fgets(newPassword, MAX_PASSWORD_LENGTH, stdin);
    newPassword[strcspn(newPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(currentUser.currentEmail, oldEmail) == 0 && strcmp(currentUser.password, newPassword) == 0) {
        printf("Enter new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

        strcpy(currentUser.currentEmail, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Invalid current email or password.\n");
    }
}

int main() {
    int choice;
    
    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character after number input

        if (choice == 1) {
            login();
        } else if (choice == 2) {
            changeEmail();
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}