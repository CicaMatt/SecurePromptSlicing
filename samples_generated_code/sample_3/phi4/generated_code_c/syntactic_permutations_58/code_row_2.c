#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void loginUser(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password. Please try again.\n");
    }
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *password) {
    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0) {
        strncpy(user->email, newEmail, MAX_EMAIL_LENGTH);
        printf("Email changed successfully.\n");
    } else {
        printf("Invalid credentials. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", password);

    loginUser(&user, oldEmail, password);

    if (strcmp(user.email, oldEmail) == 0 && strcmp(user.password, password) == 0) {
        printf("Enter new email: ");
        scanf("%s", newEmail);
        changeEmail(&user, oldEmail, newEmail, password);
    }

    printf("Current email: %s\n", user.email);

    return 0;
}