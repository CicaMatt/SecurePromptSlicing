#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User loggedUser = {"user@example.com", "securepassword"};

int authenticate(const char *email, const char *password) {
    return strcmp(email, loggedUser.email) == 0 && strcmp(password, loggedUser.password) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm password: ");
    scanf("%49s", confirmPassword);

    if (authenticate(oldEmail, confirmPassword)) {
        strcpy(loggedUser.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or confirm password.\n");
    }
}

int main() {
    changeEmail();
    return 0;
}