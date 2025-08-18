#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[50];
} User;

void login(User *user) {
    char input_username[50], input_password[50];

    printf("Enter username: ");
    scanf("%s", input_username);

    if (strcmp(user->username, input_username) != 0) {
        printf("Invalid username!\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", input_password);

    if (strcmp(user->password, input_password) != 0) {
        printf("Incorrect password!\n");
        return;
    }

    printf("Login successful.\n");
}

void changeEmail(User *user) {
    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH];
    char confirm_password[50];

    printf("\nEnter your old email: ");
    scanf("%s", old_email);

    if (strcmp(user->email, old_email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", new_email);

    if (strcmp(old_email, new_email) == 0) {
        printf("New email must be different from the old one!\n");
        return;
    }

    printf("Enter your password to confirm change: ");
    scanf("%s", confirm_password);

    if (strcmp(user->password, confirm_password) != 0) {
        printf("Incorrect password!\n");
        return;
    }

    strcpy(user->email, new_email);
    printf("\nEmail changed successfully! New email: %s\n", user->email);
}

int main() {
    User user = {"user1", "old@example.com", "password123"};

    char continue_program = 'y';

    while (continue_program == 'y' || continue_program == 'Y') {
        printf("\n1. Login\n2. Change Email\n3. Exit\n");
        char choice;
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                login(&user);
                break;
            case '2':
                changeEmail(&user);
                break;
            case '3':
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &continue_program);
    }

    return 0;
}