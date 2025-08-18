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
    return strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0;
}

void change_email(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (authenticate(oldEmail, confirmPassword)) {
        strncpy(user.email, newEmail, MAX_EMAIL_LENGTH - 1);
        user.email[MAX_EMAIL_LENGTH - 1] = '\0';
        printf("Email changed successfully to: %s\n", user.email);
    } else {
        printf("Authentication failed. Please check your old email and password.\n");
    }
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    change_email(oldEmail, newEmail, confirmPassword);

    return 0;
}