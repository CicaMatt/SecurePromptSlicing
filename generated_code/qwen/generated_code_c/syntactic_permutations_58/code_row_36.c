#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const User* user, const char* oldEmail, const char* password) {
    return strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User* user, const char* newEmail) {
    strncpy(user->email, newEmail, MAX_EMAIL_LENGTH);
    user->email[MAX_EMAIL_LENGTH - 1] = '\0';
}

int main() {
    User currentUser = {"example@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (authenticate(&currentUser, oldEmail, password)) {
        printf("Authentication successful.\nEnter new email: ");
        fgets(newEmail, sizeof(newEmail), stdin);
        newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character
        changeEmail(&currentUser, newEmail);
        printf("Email changed successfully. New email is %s\n", currentUser.email);
    } else {
        printf("Authentication failed. Email not changed.\n");
    }

    return 0;
}