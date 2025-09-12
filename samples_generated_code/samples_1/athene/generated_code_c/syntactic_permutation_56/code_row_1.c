#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 256
#define MAX_PASSWORD 20

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int authenticate(const User *user, const char *password) {
    return strcmp(user->password, password) == 0;
}

int change_email(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (!authenticate(user, confirmPassword)) {
        printf("Incorrect password.\n");
        return 0;
    }
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match the current email.\n");
        return 0;
    }
    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 0;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to: %s\n", user->email);
    return 1;
}

int main() {
    User user = {"user@example.com", "password123"};

    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    scanf("%255s", oldEmail);
    printf("Enter your new email: ");
    scanf("%255s", newEmail);
    printf("Confirm password: ");
    scanf("%19s", confirmPassword);

    change_email(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}