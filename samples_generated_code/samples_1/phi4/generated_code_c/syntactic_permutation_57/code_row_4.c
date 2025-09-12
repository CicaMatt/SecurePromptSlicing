#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct User {
    char username[100];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User loggedInUser = {"john_doe", "old_email@example.com", "securepassword123"};

int verifyLogin(const char *username, const char *password) {
    return strcmp(username, loggedInUser.username) == 0 && strcmp(password, loggedInUser.password) == 0;
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (strcmp(user->email, old_email) != 0 || strcmp(confirm_password, user->password) != 0) {
        printf("Invalid credentials. Email or password does not match.\n");
        return;
    }

    // Simulate checking if the new email is already in use
    char existingEmails[][MAX_EMAIL_LENGTH] = {"user1@example.com", "user2@example.com"};
    for (int i = 0; i < sizeof(existingEmails) / sizeof(existingEmails[0]); ++i) {
        if (strcmp(new_email, existingEmails[i]) == 0) {
            printf("The new email is already in use. Please choose a different one.\n");
            return;
        }
    }

    strcpy(user->email, new_email);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    char username[100], password[MAX_PASSWORD_LENGTH];
    printf("Enter your username: ");
    scanf("%99s", username);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (!verifyLogin(username, password)) {
        printf("Invalid login credentials.\n");
        return 1;
    }

    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], confirm_password[MAX_PASSWORD_LENGTH];
    printf("Enter your current email: ");
    scanf("%99s", old_email);
    printf("Enter your new email: ");
    scanf("%99s", new_email);
    printf("Confirm your password: ");
    scanf("%49s", confirm_password);

    changeEmail(&loggedInUser, old_email, new_email, confirm_password);

    return 0;
}