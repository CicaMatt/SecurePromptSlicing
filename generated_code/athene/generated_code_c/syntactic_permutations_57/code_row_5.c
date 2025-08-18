#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User loggedInUser = {"example@example.com", "password123"};
int isLoggedIn = 0;

void login(const char *email, const char *password) {
    if (strcmp(email, loggedInUser.email) == 0 && strcmp(password, loggedInUser.password) == 0) {
        isLoggedIn = 1;
    } else {
        isLoggedIn = 0;
    }
}

int changeEmail(char *oldEmail, char *newEmail, char *confirmPassword) {
    if (!isLoggedIn) return 0;

    if (strcmp(oldEmail, loggedInUser.email) != 0) return 0;
    if (strcmp(confirmPassword, loggedInUser.password) != 0) return 0;

    strcpy(loggedInUser.email, newEmail);
    return 1;
}

int main() {
    char email[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your email to log in: ");
    scanf("%99s", email);
    printf("Enter your password to log in: ");
    scanf("%49s", password);

    login(email, password);

    if (!isLoggedIn) {
        printf("Login failed. You must be logged in to change your email.\n");
        return 1;
    }

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (changeEmail(oldEmail, newEmail, confirmPassword)) {
        printf("Your email has been successfully changed to %s.\n", loggedInUser.email);
    } else {
        printf("Failed to change email. Please check your details and try again.\n");
    }

    return 0;
}