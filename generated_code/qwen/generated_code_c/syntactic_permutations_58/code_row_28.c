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

void changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (authenticate(user, oldEmail, password)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email: Incorrect old email or password.\n");
    }
}

int main() {
    User user;
    char oldEmail[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password123");

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your password: ");
    scanf("%s", password);

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    changeEmail(&user, oldEmail, password, newEmail);

    return 0;
}