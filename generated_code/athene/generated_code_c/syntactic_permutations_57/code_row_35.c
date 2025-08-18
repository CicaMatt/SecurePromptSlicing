#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User currentUser = {"example@example.com", "password123"};

int login(const char *email, const char *password) {
    if (strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Your email has been successfully changed to %s\n", currentUser.email);
}

int main() {
    char email[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];

    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    if (!login(email, password)) {
        printf("Login failed. Incorrect email or password.\n");
        return 1;
    }

    changeEmail();

    return 0;
}