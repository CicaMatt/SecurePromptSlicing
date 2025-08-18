#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (login(user, oldEmail, password)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (login(&user, oldEmail, password)) {
        printf("Login successful.\n");
        printf("Enter your new email: ");
        scanf("%99s", newEmail);
        changeEmail(&user, oldEmail, password, newEmail);
    } else {
        printf("Incorrect email or password. Login failed.\n");
    }

    return 0;
}