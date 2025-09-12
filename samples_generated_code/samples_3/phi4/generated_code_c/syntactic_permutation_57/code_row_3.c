#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User loggedInUser = {"example@domain.com", "", "password123"}; // Example logged-in user data

int verifyPassword(const char *inputPassword) {
    return strcmp(inputPassword, loggedInUser.password) == 0;
}

int isEmailDifferent(const char *old_email, const char *new_email) {
    return strcmp(old_email, new_email) != 0;
}

void changeEmail() {
    User user;
    printf("Enter old email: ");
    fgets(user.old_email, MAX_EMAIL_LENGTH, stdin);
    user.old_email[strcspn(user.old_email, "\n")] = '\0'; // Remove newline character

    if (strcmp(user.old_email, loggedInUser.old_email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter new email: ");
    fgets(user.new_email, MAX_EMAIL_LENGTH, stdin);
    user.new_email[strcspn(user.new_email, "\n")] = '\0'; // Remove newline character

    if (strcmp(user.old_email, user.new_email) == 0) {
        printf("New email must be different from old email.\n");
        return;
    }

    char inputPassword[MAX_PASSWORD_LENGTH];
    printf("Enter password: ");
    fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    if (!verifyPassword(inputPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    loggedInUser.old_email[0] = '\0'; // Clear old email
    strcpy(loggedInUser.old_email, user.new_email); // Update to new email

    printf("Email changed successfully!\n");
}

int main() {
    changeEmail();
    return 0;
}