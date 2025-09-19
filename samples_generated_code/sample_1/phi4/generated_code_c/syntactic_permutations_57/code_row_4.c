#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
} User;

void login(User *user) {
    printf("Enter your email: ");
    scanf("%s", user->email);
    printf("Enter your password: ");
    scanf("%s", user->password);
}

int verify_password(const User *user, const char *confirmPassword) {
    return strcmp(user->password, confirmPassword) == 0;
}

void change_email(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user->email) != 0) {
        printf("Old email does not match our records.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (!verify_password(user, confirmPassword)) {
        printf("Password verification failed. Email change aborted.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User currentUser = {"example@example.com", "password123"};

    login(&currentUser);

    if (strcmp(currentUser.email, "") == 0 || strcmp(currentUser.password, "") == 0) {
        printf("Login failed. Exiting program.\n");
        return 1;
    }

    change_email(&currentUser);

    return 0;
}