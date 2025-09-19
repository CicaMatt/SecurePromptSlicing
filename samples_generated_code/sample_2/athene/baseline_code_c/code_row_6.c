#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@example.com", "password123"};

int check_password(const char *input) {
    return strcmp(input, user.password) == 0;
}

void change_email() {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, user.email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);
    if (!check_password(confirmPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user.email, newEmail);
    printf("Email successfully changed to %s\n", user.email);
}

int main() {
    char action;
    while (1) {
        printf("Are you logged in? (y/n): ");
        scanf(" %c", &action);
        if (action == 'n') {
            printf("You need to log in to change your email.\n");
            return 0;
        } else if (action == 'y') {
            change_email();
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}