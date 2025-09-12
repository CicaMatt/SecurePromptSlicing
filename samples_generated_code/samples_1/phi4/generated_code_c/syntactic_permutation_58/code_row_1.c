#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

void login(User *user, const char *inputEmail, const char *inputPassword) {
    if (strcmp(user->email, inputEmail) == 0 && strcmp(user->password, inputPassword) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail(User *user, const char *oldEmail, const char *inputPassword, const char *newEmail) {
    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, inputPassword) == 0) {
        strncpy(user->email, newEmail, MAX_EMAIL_LENGTH);
        printf("Email changed successfully to %s\n", user->email);
    } else {
        printf("Old email or password incorrect. Email not changed.\n");
    }
}

int main() {
    User user = {"JohnDoe", "john@example.com", "password123"};

    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[PASSWORD_LENGTH];

    printf("Enter your email: ");
    fgets(inputEmail, MAX_EMAIL_LENGTH, stdin);
    inputEmail[strcspn(inputEmail, "\n")] = 0;

    printf("Enter your password: ");
    fgets(inputPassword, PASSWORD_LENGTH, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = 0;

    login(&user, inputEmail, inputPassword);

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email to change: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(newPassword, PASSWORD_LENGTH, stdin);
    newPassword[strcspn(newPassword, "\n")] = 0;

    printf("Enter new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    changeEmail(&user, oldEmail, newPassword, newEmail);

    return 0;
}