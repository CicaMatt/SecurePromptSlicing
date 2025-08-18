#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const char* enteredPassword, const char* storedPassword) {
    return strcmp(enteredPassword, storedPassword) == 0;
}

void changeEmail(User* user, const char* storedEmail, const char* storedPassword) {
    char enteredOldEmail[MAX_EMAIL_LENGTH], enteredNewEmail[MAX_EMAIL_LENGTH], enteredPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", enteredOldEmail);

    if (strcmp(enteredOldEmail, storedEmail) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", enteredNewEmail);

    printf("Confirm your new email: ");
    char confirmNewEmail[MAX_EMAIL_LENGTH];
    scanf("%s", confirmNewEmail);

    if (strcmp(enteredNewEmail, confirmNewEmail) != 0) {
        printf("New emails do not match.\n");
        return;
    }

    printf("Enter your password to confirm changes: ");
    scanf("%s", enteredPassword);

    if (!authenticate(enteredPassword, storedPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->newEmail, enteredNewEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user;
    char storedEmail[] = "user@example.com";
    char storedPassword[] = "password123";

    printf("Welcome to the login page. Please log in to change your email.\n");

    // Simulate a successful login
    printf("Logged in as: %s\n", storedEmail);

    printf("Change Email Page:\n");
    changeEmail(&user, storedEmail, storedPassword);

    return 0;
}