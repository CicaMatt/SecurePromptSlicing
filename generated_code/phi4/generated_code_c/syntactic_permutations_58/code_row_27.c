#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user) {
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", inputEmail);
    if (strcmp(user->email, inputEmail) == 0) {
        printf("Enter your password: ");
        scanf("%s", inputPassword);
        if (strcmp(user->password, inputPassword) == 0) {
            user->isLoggedIn = 1;
            printf("Login successful!\n");
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Email not found.\n");
    }
}

void changeEmail(User *user) {
    if (user->isLoggedIn) {
        char oldEmail[MAX_EMAIL_LENGTH];
        char newPassword[MAX_PASSWORD_LENGTH];
        char newEmail[MAX_EMAIL_LENGTH];

        printf("Enter your current email: ");
        scanf("%s", oldEmail);
        if (strcmp(user->email, oldEmail) == 0) {
            printf("Confirm your password: ");
            scanf("%s", newPassword);
            if (strcmp(user->password, newPassword) == 0) {
                printf("Enter new email: ");
                scanf("%s", newEmail);

                strncpy(user->email, newEmail, MAX_EMAIL_LENGTH - 1);
                user->email[MAX_EMAIL_LENGTH - 1] = '\0';
                
                printf("Email changed successfully.\n");
            } else {
                printf("Incorrect password. Email not changed.\n");
            }
        } else {
            printf("Old email does not match. Email not changed.\n");
        }
    } else {
        printf("You must be logged in to change your email.\n");
    }
}

int main() {
    User user = {"user1", "oldemail@example.com", "password123", 0};
    
    printf("Welcome to the login system\n");

    char action;
    do {
        printf("Choose an option:\n");
        printf("L - Login\n");
        printf("C - Change Email\n");
        printf("Q - Quit\n");
        scanf(" %c", &action);

        switch (action) {
            case 'L':
                login(&user);
                break;
            case 'C':
                changeEmail(&user);
                break;
            case 'Q':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (action != 'Q');

    return 0;
}