#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[50]; // Storing passwords in plaintext for simplicity; use hashing in production.
} User;

User currentUser = {"user@example.com", "password123"}; // Example user data.

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPass[50];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character.

    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character.

    if (strcmp(user->email, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Enter your password: ");
    fgets(confirmPass, 50, stdin);
    confirmPass[strcspn(confirmPass, "\n")] = '\0'; // Remove newline character.

    if (strcmp(user->password, confirmPass) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to: %s\n", user->email);
}

int main() {
    char choice;

    do {
        printf("\nSimple Login System\n");
        printf("1. Change Email\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%c", &choice);
        getchar(); // Consume the newline character after %c input.

        switch (choice) {
            case '1':
                changeEmail(&currentUser);
                break;
            case '2':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '2');

    return 0;
}