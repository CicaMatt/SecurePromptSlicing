#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
} User;

User currentUser = {"user1", "user@example.com", "password123"};
int loggedIn = 0;

void displayLoginPage() {
    printf("Login Page\n");
    printf("Username: ");
    scanf("%s", currentUser.username);
    printf("Password: ");
    scanf("%s", currentUser.password);

    if (strcmp(currentUser.username, "user1") == 0 && strcmp(currentUser.password, "password123") == 0) {
        loggedIn = 1;
        printf("Login successful!\n");
    } else {
        loggedIn = 0;
        printf("Invalid username or password.\n");
    }
}

void displayChangeEmailPage() {
    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char old_email[MAX_LENGTH], new_email[MAX_LENGTH], confirm_password[MAX_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", old_email);
    if (strcmp(old_email, currentUser.email) != 0) {
        printf("Invalid old email provided.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", new_email);

    printf("Confirm password: ");
    scanf("%s", confirm_password);
    if (strcmp(confirm_password, currentUser.password) != 0) {
        printf("Incorrect confirm password.\n");
        return;
    }

    strcpy(currentUser.email, new_email);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayLoginPage();
                break;
            case 2:
                displayChangeEmailPage();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}