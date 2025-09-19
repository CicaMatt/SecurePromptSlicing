#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void changeEmail(User *user, const char *oldEmail, const char *password) {
    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0) {
        printf("Enter new email: ");
        scanf("%s", user->email);
        printf("Email changed successfully!\n");
    } else {
        printf("Old email or password incorrect. Email not changed.\n");
    }
}

int main() {
    User currentUser = {"user@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Logged in as: %s\n", currentUser.email);

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", password);

    changeEmail(&currentUser, oldEmail, password);

    printf("Current email: %s\n", currentUser.email);

    return 0;
}