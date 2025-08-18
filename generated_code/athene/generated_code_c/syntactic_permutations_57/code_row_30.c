#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@example.com", "password123"};

int authenticate(const char *email, const char *password) {
    return strcmp(email, user.email) == 0 && strcmp(password, user.password) == 0;
}

void changeEmail(char *newEmail) {
    strncpy(user.email, newEmail, MAX_EMAIL_LENGTH - 1);
    user.email[MAX_EMAIL_LENGTH - 1] = '\0';
    printf("Email changed successfully. New email: %s\n", user.email);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);

    printf("Enter your password: ");
    scanf("%19s", newPassword);

    if (!authenticate(oldEmail, newPassword)) {
        printf("Incorrect email or password.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%49s", newEmail);

    printf("Confirm password: ");
    scanf("%19s", confirmPassword);

    if (strcmp(confirmPassword, user.password) != 0) {
        printf("Incorrect confirm password.\n");
        return 1;
    }

    changeEmail(newEmail);
    return 0;
}