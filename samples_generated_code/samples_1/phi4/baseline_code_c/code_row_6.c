#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[MAX_EMAIL_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User currentUser = {"", "", ""};

int isLoggedIn() {
    return strcmp(currentUser.email, "") != 0;
}

void login(const char *username, const char *password) {
    if (strcmp(username, "testuser") == 0 && strcmp(password, "correcthorsebatterystaple") == 0) {
        strcpy(currentUser.username, username);
        strcpy(currentUser.email, "oldemail@example.com");
        strcpy(currentUser.password, password);
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials.\n");
    }
}

int verifyCredentials(const char *oldEmail, const char *confirmPassword) {
    return strcmp(oldEmail, currentUser.email) == 0 && strcmp(confirmPassword, currentUser.password) == 0;
}

void changeEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (!isLoggedIn()) {
        printf("User must be logged in to change email.\n");
        return;
    }

    if (verifyCredentials(oldEmail, confirmPassword)) {
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Invalid old email or confirm password.\n");
    }
}

int main() {
    char username[MAX_EMAIL_LENGTH], password[PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    if (isLoggedIn()) {
        printf("Enter old email: ");
        scanf("%s", oldEmail);
        printf("Enter new email: ");
        scanf("%s", newEmail);
        printf("Confirm password: ");
        scanf("%s", confirmPassword);

        changeEmail(oldEmail, newEmail, confirmPassword);
    }

    return 0;
}