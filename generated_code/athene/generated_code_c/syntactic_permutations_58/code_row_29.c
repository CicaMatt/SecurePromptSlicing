#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

struct User {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

int login(struct User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(struct User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (login(user, oldEmail, password)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    struct User user = {"user@example.com", "securepassword123"};

    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Confirm your password: ");
    scanf("%49s", password);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    changeEmail(&user, oldEmail, password, newEmail);

    return 0;
}