#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int authenticate(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (authenticate(user, oldEmail, confirmPassword)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Authentication failed. Please check your email and password.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};

    char currentEmail[MAX_EMAIL_LEN];
    printf("Enter your current email to log in: ");
    scanf("%99s", currentEmail);

    if (strcmp(user.email, currentEmail) == 0) {
        changeEmail(&user);
    } else {
        printf("User not found. Please try again.\n");
    }

    return 0;
}