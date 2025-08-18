#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user, const char *oldEmail, const char *newEmail, const char *password) {
    if (authenticate(user, oldEmail, password)) {
        if (strcmp(oldEmail, newEmail) != 0) {
            strncpy(user->email, newEmail, MAX_EMAIL_LENGTH - 1);
            user->email[MAX_EMAIL_LENGTH - 1] = '\0';
            printf("Email changed successfully to %s\n", user->email);
        } else {
            printf("New email must be different from the old email.\n");
        }
    } else {
        printf("Authentication failed. Password incorrect or email does not match.\n");
    }
}

int main() {
    User currentUser = {"user@example.com", "securepassword"};

    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    change_email(&currentUser, oldEmail, newEmail, password);

    return 0;
}