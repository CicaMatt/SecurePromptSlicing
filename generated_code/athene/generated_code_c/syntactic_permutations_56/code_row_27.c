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

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *password) {
    if (login(user, oldEmail, password)) {
        if (strcmp(oldEmail, newEmail) != 0) {
            strcpy(user->email, newEmail);
            printf("Email changed successfully.\n");
        } else {
            printf("New email must be different from the old email.\n");
        }
    } else {
        printf("Incorrect email or password.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Enter your password: ");
    scanf("%49s", password);

    changeEmail(&user, oldEmail, newEmail, password);

    return 0;
}