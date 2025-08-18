#include <stdio.h>
#include <string.h>

// User structure to hold login credentials
typedef struct {
    char username[50];
    char email[100];
    char password[50];
    int isLoggedIn;
} User;

User currentUser = {"user1", "oldemail@example.com", "password123", 0};

void displayMenu() {
    printf("\nLogin Menu:\n");
    printf("1. Login\n2. Change Email (Logged in only)\n3. Exit\n");
}

int login(char *username, char *password) {
    if (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0) {
        currentUser.isLoggedIn = 1;
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Incorrect username or password.\n");
        return 0;
    }
}

int changeEmail(char *oldEmail, char *password, char *newEmail) {
    if (currentUser.isLoggedIn && strcmp(currentUser.email, oldEmail) == 0 && strcmp(password, currentUser.password) == 0) {
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully to %s\n", newEmail);
        return 1;
    } else {
        printf("Failed to change email. Check your current email and password.\n");
        return 0;
    }
}

int main() {
    int choice;
    char username[50], password[50], oldEmail[100], newEmail[100];

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                login(username, password);
                break;

            case 2:
                if (!currentUser.isLoggedIn) {
                    printf("You must be logged in to change your email.\n");
                } else {
                    printf("Enter current email: ");
                    scanf("%s", oldEmail);
                    printf("Enter password: ");
                    scanf("%s", password);
                    printf("Enter new email: ");
                    scanf("%s", newEmail);
                    changeEmail(oldEmail, password, newEmail);
                }
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