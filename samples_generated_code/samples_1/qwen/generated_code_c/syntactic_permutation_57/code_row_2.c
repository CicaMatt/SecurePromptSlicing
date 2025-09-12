#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int authenticateUser(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *newEmail) {
    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "password123"};
    char oldEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
    char newEmail[MAX_EMAIL];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (!authenticateUser(&user, oldEmail, confirmPassword)) {
        printf("Authentication failed. Please check your old email and password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    changeEmail(&user, newEmail);

    return 0;
}