#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* email, const char* password) {
    // Dummy authentication logic
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

void changeEmail(User* user) {
    if (authenticateUser(user->oldEmail, user->password)) {
        printf("Email changed successfully from %s to %s.\n", user->oldEmail, user->newEmail);
    } else {
        printf("Failed to change email. Please check your old email and password.\n");
    }
}

int main() {
    User user;

    printf("Enter your current email: ");
    scanf("%99s", user.oldEmail);

    if (!authenticateUser(user.oldEmail, "")) {
        printf("You must be logged in to change your email.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%99s", user.newEmail);

    printf("Confirm your password: ");
    scanf("%49s", user.password);

    changeEmail(&user);

    return 0;
}