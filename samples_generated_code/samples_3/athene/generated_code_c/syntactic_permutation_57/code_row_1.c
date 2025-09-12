#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@example.com", "password123"};

int authenticate(const char *email, const char *password) {
    return (strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0);
}

void change_email() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user.email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (!authenticate(oldEmail, confirmPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user.email, newEmail);
    printf("Email changed successfully to %s.\n", user.email);
}

int main() {
    change_email();
    return 0;
}