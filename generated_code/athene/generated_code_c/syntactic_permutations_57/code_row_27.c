#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
} User;

int authenticate(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user, const char *oldEmail, const char *newEmail, const char *confirm) {
    if (authenticate(user, oldEmail, confirm)) {
        strncpy(user->email, newEmail, MAX_EMAIL_LENGTH - 1);
        user->email[MAX_EMAIL_LENGTH - 1] = '\0';
        printf("Email changed successfully.\n");
    } else {
        printf("Authentication failed. Cannot change email.\n");
    }
}

int main() {
    User currentUser = {"user@example.com", "password123"};

    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirm[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm with your password: ");
    scanf("%99s", confirm);

    change_email(&currentUser, oldEmail, newEmail, confirm);

    return 0;
}