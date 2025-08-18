#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User loggedInUser = {"example@example.com", "password123"};

int authenticate(const char *email, const char *password) {
    return strcmp(email, loggedInUser.email) == 0 && strcmp(password, loggedInUser.password) == 0;
}

void changeEmail(char *newEmail) {
    strncpy(loggedInUser.email, newEmail, MAX_EMAIL_LENGTH - 1);
    loggedInUser.email[MAX_EMAIL_LENGTH - 1] = '\0';
    printf("Email changed successfully to: %s\n", loggedInUser.email);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char confirmNewPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);

    if (strcmp(oldEmail, loggedInUser.email) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your current password to confirm: ");
    scanf("%49s", newPassword);

    if (!authenticate(loggedInUser.email, newPassword)) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    changeEmail(newEmail);

    return 0;
}