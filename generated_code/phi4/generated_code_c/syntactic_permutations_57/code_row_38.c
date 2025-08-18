#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[20];
} User;

User loggedInUser = {"user1", "oldemail@example.com", "password123"};

void changeEmail() {
    char oldEmail[100];
    char newEmail[100];
    char confirmPassword[20];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, loggedInUser.email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm password: ");
    scanf("%19s", confirmPassword);
    if (strcmp(confirmPassword, loggedInUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(loggedInUser.email, newEmail);
    printf("Email changed successfully to %s\n", newEmail);
}

int main() {
    int choice;

    do {
        printf("\n1. Change Email\n2. Logout\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                changeEmail();
                break;
            case 2:
                loggedInUser.username[0] = '\0'; // Simulate logout by clearing username
                printf("Logged out successfully.\n");
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}