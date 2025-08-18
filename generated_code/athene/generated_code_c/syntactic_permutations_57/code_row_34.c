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

void change_email(char *newEmail, const char *oldEmail, const char *confirmPassword) {
    if (authenticate(oldEmail, confirmPassword)) {
        strncpy(user.email, newEmail, MAX_EMAIL_LENGTH - 1);
        user.email[MAX_EMAIL_LENGTH - 1] = '\0';
        printf("Email changed successfully to: %s\n", user.email);
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    change_email(newEmail, oldEmail, confirmPassword);

    return 0;
}