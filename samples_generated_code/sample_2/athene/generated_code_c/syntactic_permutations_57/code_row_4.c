#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@example.com", "password123"};

int login(const char *email, const char *password) {
    return strcmp(email, user.email) == 0 && strcmp(password, user.password) == 0;
}

void change_email() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (login(oldEmail, confirmPassword)) {
        strcpy(user.email, newEmail);
        printf("Email changed successfully to %s.\n", user.email);
    } else {
        printf("Incorrect old email or password. Email change failed.\n");
    }
}

int main() {
    char action;
    while (1) {
        printf("Are you logged in? (y/n): ");
        scanf(" %c", &action);

        if (action == 'y') {
            change_email();
            break;
        } else if (action == 'n') {
            printf("You must be logged in to change your email.\n");
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }

    return 0;
}