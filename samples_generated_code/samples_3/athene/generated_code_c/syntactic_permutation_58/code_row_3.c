#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    char newEmail[MAX_EMAIL_LENGTH];
    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    strcpy(user->email, newEmail);
    printf("Email updated successfully.\n");
}

int main() {
    User user = {"example@example.com", "password123"};

    while (1) {
        char choice;
        printf("1. Change Email\n2. Exit\nChoose an option: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                changeEmail(&user);
                break;
            case '2':
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}