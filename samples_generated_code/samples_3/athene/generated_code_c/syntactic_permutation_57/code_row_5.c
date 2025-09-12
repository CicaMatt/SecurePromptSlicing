#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User loggedInUser = {"user@example.com", "password123"};

int authenticate(const char *email, const char *password) {
    return strcmp(email, loggedInUser.email) == 0 && strcmp(password, loggedInUser.password) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (authenticate(oldEmail, confirmPassword)) {
        strcpy(loggedInUser.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Authentication failed. Please check your email and password.\n");
    }
}

int main() {
    printf("Logged in as: %s\n", loggedInUser.email);

    changeEmail();

    printf("New email is: %s\n", loggedInUser.email);
    return 0;
}