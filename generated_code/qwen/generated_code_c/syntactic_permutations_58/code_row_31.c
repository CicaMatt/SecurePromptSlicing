#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int authenticateUser(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (authenticateUser(user, oldEmail, password)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    User user;
    char oldEmail[MAX_EMAIL], password[MAX_PASSWORD], newEmail[MAX_EMAIL];

    // Initialize user with default values
    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password123");

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    changeEmail(&user, oldEmail, password, newEmail);

    return 0;
}