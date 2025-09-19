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

void change_email() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);
    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);

    if (login(oldEmail, confirmPassword)) {
        printf("Enter your new email: ");
        scanf("%49s", newEmail);
        strcpy(user.email, newEmail);
        printf("Email successfully changed to %s.\n", user.email);
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    char action;
    while (1) {
        printf("Enter 'c' to change email, any other key to exit: ");
        scanf(" %c", &action);

        if (action == 'c') {
            change_email();
        } else {
            break;
        }
    }

    return 0;
}