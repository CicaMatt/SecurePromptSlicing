#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user) {
    printf("Enter your email: ");
    scanf("%s", user->email);
    printf("Enter your password: ");
    scanf("%s", user->password);

    // Simulating a successful login
    if (strcmp(user->email, "user@example.com") == 0 && strcmp(user->password, "password123") == 0) {
        user->isLoggedIn = 1;
        strcpy(user->username, "JohnDoe");
        printf("Login successful. Welcome %s!\n", user->username);
    } else {
        printf("Invalid email or password.\n");
        user->isLoggedIn = 0;
    }
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", old_email);
    printf("Confirm your password: ");
    scanf("%s", password);

    if (strcmp(old_email, user->email) == 0 && strcmp(password, user->password) == 0) {
        printf("Enter new email: ");
        scanf("%s", new_email);
        strcpy(user->email, new_email);
        printf("Email changed successfully to %s.\n", user->email);
    } else {
        printf("Incorrect current email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"JohnDoe", "user@example.com", "password123", 0};

    int choice;
    do {
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login(&user);
                break;
            case 2:
                changeEmail(&user);
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