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

void changeEmail(User *user) {
    char currentPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current password: ");
    scanf("%49s", currentPassword);

    if (!login(user, user->email, currentPassword)) {
        printf("Incorrect password. Email change failed.\n");
        return;
    }

    printf("Enter your new email address: ");
    scanf("%99s", newEmail);

    if (strcmp(newEmail, user->email) == 0) {
        printf("New email is the same as the old one. No changes made.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to: %s\n", user->email);
}

int main() {
    User user = {"example@example.com", "password123"};
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%99s", email);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (!login(&user, email, password)) {
        printf("Login failed. Please check your credentials and try again.\n");
        return 1;
    }

    changeEmail(&user);

    return 0;
}