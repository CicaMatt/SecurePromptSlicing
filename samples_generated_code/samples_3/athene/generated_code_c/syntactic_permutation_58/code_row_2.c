#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@example.com", "password123"};

int login(const char *email, const char *password) {
    return strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);

    if (login(oldEmail, confirmPassword)) {
        printf("Enter your new email: ");
        scanf("%49s", newEmail);
        strcpy(user.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Change Email\n2. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                changeEmail();
                break;
            case 2:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}