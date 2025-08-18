#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User currentUser = {"user@example.com", "password123"};

int login(const char *email, const char *password) {
    if (strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(char newEmail[MAX_EMAIL_LEN], const char *oldEmail, const char *confirmPassword) {
    if (!login(oldEmail, confirmPassword)) {
        printf("Incorrect old email or password.\n");
        return;
    }

    if (strlen(newEmail) == 0 || !strstr(newEmail, "@")) {
        printf("Invalid new email address.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email successfully changed to: %s\n", currentUser.email);
}

int main() {
    char oldEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];
    char newEmail[MAX_EMAIL_LEN];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);

    printf("Confirm password: ");
    scanf("%49s", confirmPassword);

    printf("Enter new email: ");
    scanf("%99s", newEmail);

    changeEmail(newEmail, oldEmail, confirmPassword);

    return 0;
}