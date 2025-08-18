#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User currentUser;
int isLoggedIn = 0;

void login(User *user) {
    printf("Enter username: ");
    scanf("%s", user->username);
    
    printf("Enter email: ");
    scanf("%s", user->email);
    
    printf("Enter password: ");
    scanf("%s", user->password);

    isLoggedIn = 1;
}

void updateEmail(User *user) {
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char confirm_password[MAX_PASSWORD_LEN];

    if (!isLoggedIn) {
        printf("You must be logged in to change email.\n");
        return;
    }

    printf("Enter your current email: ");
    scanf("%s", old_email);
    
    if (strcmp(old_email, user->email) != 0) {
        printf("Email does not match our records. Try again.\n");
        return;
    }
    
    printf("Enter new email: ");
    scanf("%s", new_email);

    if (strcmp(new_email, old_email) == 0) {
        printf("New email must be different from the current one.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirm_password);
    
    if (strcmp(confirm_password, user->password) != 0) {
        printf("Password incorrect. Try again.\n");
        return;
    }
    
    strcpy(user->email, new_email);
    printf("Email updated successfully!\n");
}

int main() {
    int choice;

    while (1) {
        if (!isLoggedIn) {
            printf("\n1. Login\n2. Exit\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    login(&currentUser);
                    break;
                case 2:
                    return 0;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } else {
            printf("\n1. Change Email\n2. Logout\n3. Exit\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    updateEmail(&currentUser);
                    break;
                case 2:
                    isLoggedIn = 0;
                    printf("You have been logged out.\n");
                    break;
                case 3:
                    return 0;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }

    return 0;
}