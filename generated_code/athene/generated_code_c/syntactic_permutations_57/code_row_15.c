#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const User *user, const char *email, const char *password) {
    return (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0);
}

void changeEmail(User *user, const char *newEmail) {
    strcpy(user->email, newEmail);
}

int main() {
    User user = {"example@example.com", "securepassword123"};
    char oldEmail[MAX_EMAIL_LENGTH], newPassword[MAX_PASSWORD_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm password: ");
    scanf("%49s", confirmPassword);

    if (authenticate(&user, oldEmail, confirmPassword)) {
        changeEmail(&user, newEmail);
        printf("Email changed successfully. New email: %s\n", user.email);
    } else {
        printf("Authentication failed. Email or password is incorrect.\n");
    }

    return 0;
}