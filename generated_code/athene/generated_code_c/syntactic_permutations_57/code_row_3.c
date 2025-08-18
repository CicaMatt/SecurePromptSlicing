#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"user@example.com", "password123"};

int authenticate(const char* email, const char* password) {
    return strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0;
}

void changeEmail(char *newEmail) {
    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully. New email: %s\n", currentUser.email);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (authenticate(oldEmail, confirmPassword)) {
        changeEmail(newEmail);
    } else {
        printf("Incorrect password.\n");
        return 1;
    }

    return 0;
}