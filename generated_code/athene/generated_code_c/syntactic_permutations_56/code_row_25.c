#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

int changeEmail(User *user, const char *newEmail, const char *currentPassword) {
    if (login(user, user->email, currentPassword)) {
        if (strcmp(newEmail, user->email) != 0) {
            strncpy(user->email, newEmail, MAX_EMAIL_LENGTH - 1);
            user->email[MAX_EMAIL_LENGTH - 1] = '\0';
            return 1; // Success
        }
    }
    return 0; // Failure
}

int main() {
    User user = {"example@example.com", "password123"};
    char currentEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    fgets(currentEmail, MAX_EMAIL_LENGTH, stdin);
    currentEmail[strcspn(currentEmail, "\n")] = 0;

    printf("Enter your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (login(&user, currentEmail, confirmPassword)) {
        printf("Enter new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = 0;

        if (changeEmail(&user, newEmail, confirmPassword)) {
            printf("Email changed successfully to %s\n", user.email);
        } else {
            printf("Failed to change email. Please ensure the new email is different from the current one.\n");
        }
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}