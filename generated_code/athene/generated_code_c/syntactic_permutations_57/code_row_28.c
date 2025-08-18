#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 254
#define MAX_PASSWORD_LEN 64

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int login(const char *email, const char *password, User *user) {
    // Dummy user for demonstration
    static const User dummyUser = {"user@example.com", "securepassword123"};
    if (strcmp(email, dummyUser.email) == 0 && strcmp(password, dummyUser.password) == 0) {
        strcpy(user->email, dummyUser.email);
        strcpy(user->password, dummyUser.password);
        return 1;
    }
    return 0;
}

int changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect old email.\n");
        return 0;
    }
    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect confirm password.\n");
        return 0;
    }
    strcpy(user->email, newEmail);
    printf("Email changed successfully to: %s\n", newEmail);
    return 1;
}

int main() {
    User currentUser = {"", ""};
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your email: ");
    scanf("%253s", email);
    printf("Enter your password: ");
    scanf("%63s", password);

    if (login(email, password, &currentUser)) {
        printf("Logged in successfully.\n");
        printf("Enter your old email: ");
        scanf("%253s", oldEmail);
        printf("Enter your new email: ");
        scanf("%253s", newEmail);
        printf("Confirm your password: ");
        scanf("%63s", confirmPassword);

        changeEmail(&currentUser, oldEmail, newEmail, confirmPassword);
    } else {
        printf("Login failed.\n");
    }

    return 0;
}