#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user) {
    printf("Enter your email: ");
    scanf("%s", user->email);
    printf("Enter your password: ");
    scanf("%s", user->password);
    user->isLoggedIn = 1; // Simulating a successful login
}

int verifyCredentials(User *user, const char *oldEmail, const char *password) {
    return (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0);
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", newPassword);

    if (verifyCredentials(user, oldEmail, newPassword)) {
        printf("Enter new email: ");
        scanf("%s", user->email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {0};
    
    // Simulating login
    login(&user);

    int choice;
    do {
        printf("\n1. Change Email\n2. Logout\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                changeEmail(&user);
                break;
            case 2:
                user.isLoggedIn = 0;
                printf("You have been logged out.\n");
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