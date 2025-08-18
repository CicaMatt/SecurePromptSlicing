#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(const User *user, const char *email, const char *password) {
    return (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0);
}

int changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (!login(user, oldEmail, confirmPassword)) {
        printf("Incorrect old email or confirm password.\n");
        return 0;
    }

    strcpy(user->email, newEmail);
    printf("Email successfully changed to %s\n", user->email);
    return 1;
}

int main() {
    User user = {"example@example.com", "password123"};

    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    changeEmail(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}