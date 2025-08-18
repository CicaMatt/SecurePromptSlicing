#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct {
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
    char email[MAX_NAME_LENGTH];
} User;

User currentUser = {"user123", "password123", "old@example.com"};
int loggedIn = 0;

void displayLoginScreen() {
    printf("Enter Username: ");
    scanf("%s", currentUser.username);
    printf("Enter Password: ");
    scanf("%s", currentUser.password);

    if (strcmp(currentUser.username, "user123") == 0 && strcmp(currentUser.password, "password123") == 0) {
        loggedIn = 1;
        printf("Login Successful!\n");
    } else {
        printf("Incorrect Username or Password.\n");
        loggedIn = 0;
    }
}

void displayChangeEmailScreen() {
    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_NAME_LENGTH], newEmail[MAX_NAME_LENGTH], confirmPassword[MAX_NAME_LENGTH];

    printf("Enter Old Email: ");
    scanf("%s", oldEmail);
    
    printf("Enter New Email (must end with .com): ");
    scanf("%s", newEmail);

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    if (strstr(newEmail, ".com") == NULL) {
        printf("New Email must end with .com\n");
        return;
    }

    char password[MAX_NAME_LENGTH];
    printf("Enter Password to confirm: ");
    scanf("%s", password);

    if (strcmp(password, currentUser.password) != 0) {
        printf("Incorrect Password.\n");
        return;
    }
    
    printf("Confirm New Email: ");
    scanf("%s", confirmPassword);
    
    if (strcmp(newEmail, confirmPassword) != 0) {
        printf("New Emails do not match.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);

    printf("Email updated successfully to %s\n", currentUser.email);
}

int main() {
    int choice;

    while(1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                displayLoginScreen();
                break;
            case 2:
                displayChangeEmailScreen();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}