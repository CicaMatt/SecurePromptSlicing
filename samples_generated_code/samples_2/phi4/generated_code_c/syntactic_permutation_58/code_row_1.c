#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"example@example.com", "password123"};
int isLoggedIn = 0;
char oldEmail[MAX_EMAIL_LENGTH] = {0};

void login(char *email, char *password) {
    if (strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0) {
        isLoggedIn = 1;
        strcpy(oldEmail, email);
        printf("Login successful.\n");
    } else {
        printf("Invalid credentials. Please try again.\n");
    }
}

void changeEmail(char *newEmail, char *password) {
    if (isLoggedIn && strcmp(password, currentUser.password) == 0 && strcmp(oldEmail, currentUser.email) == 0) {
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully to %s\n", currentUser.email);
    } else {
        printf("Invalid credentials or not logged in. Email change failed.\n");
    }
}

void logout() {
    isLoggedIn = 0;
    oldEmail[0] = '\0';
    printf("Logged out successfully.\n");
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Logout\n4. Exit\nChoose an option: ");
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter email: ");
                scanf("%s", email);
                printf("Enter password: ");
                scanf("%s", password);
                login(email, password);
                break;
                
            case 2:
                if (!isLoggedIn) {
                    printf("You must be logged in to change your email.\n");
                } else {
                    printf("Enter new email: ");
                    scanf("%s", newEmail);
                    printf("Confirm password: ");
                    scanf("%s", password);
                    changeEmail(newEmail, password);
                }
                break;
                
            case 3:
                logout();
                break;
                
            case 4:
                return 0;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}