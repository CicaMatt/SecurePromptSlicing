#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

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
    scanf("%99s", inputEmail);
    printf("Enter your password: ");
    scanf("%19s", inputPassword);

    if (strcmp(user->email, inputEmail) == 0 && strcmp(user->password, inputPassword) == 0) {
        user->isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        user->isLoggedIn = 0;
        printf("Invalid email or password.\n");
    }
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current (old) email: ");
    scanf("%99s", oldEmail);
    if (strcmp(user->email, oldEmail) != 0) {
        printf("The provided email does not match the account.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);
    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Incorrect password. Email change failed.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Your email has been successfully updated to %s\n", user->email);
}

int main() {
    User currentUser = {"JohnDoe", "john@example.com", "secure1234", 0};

    printf("Welcome to the Email Change Portal\n");
    
    while (1) {
        int choice;
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                login(&currentUser);
                break;
            case 2:
                changeEmail(&currentUser);
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